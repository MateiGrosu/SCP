const express = require("express");
const cors = require("cors");
const { Pool } = require("pg");
require("dotenv").config();

const app = express();
const PORT = process.env.PORT || 5001;

// PostgreSQL connection setup
const pool = new Pool({
  user: process.env.DB_USER,
  host: process.env.DB_HOST,
  database: process.env.DB_NAME,
  password: process.env.DB_PASSWORD,
  port: process.env.DB_PORT,
  ssl: {
    rejectUnauthorized: false
  }
});

const TTN_API_URL = `https://eu1.cloud.thethings.network/api/v3/as/applications/${process.env.TTN_APP_ID}/devices/${process.env.TTN_DEVICE_ID}/down/push`;
const TTN_API_KEY = `Bearer ${process.env.TTN_API_KEY}`;


app.use(cors({
  origin: ['http://localhost:3000', 'https://frontend-alarm.onrender.com']
}));

app.use(express.json()); // Parse JSON request bodies

app.get("/", (req, res) => {
  res.send("Welcome to the backend server!");
});

app.post("/temperature", async (req, res) => {
  try {
    console.log(" Received TTN Webhook Data:", JSON.stringify(req.body, null, 2));

    // Check if uplink_message exists in request
    if (!req.body.uplink_message || !req.body.uplink_message.decoded_payload) {
      console.error("ERROR: Missing 'uplink_message' in request body");
      return res.status(400).json({ error: "Invalid payload format: Missing 'uplink_message'" });
    }

    // Extract sensor data from payload
    const payload = req.body.uplink_message.decoded_payload;
    const temperature = parseFloat(payload.temperature);
    const humidity = parseFloat(payload.humidity);
    const pressure = parseFloat(payload.pressure);

    // Validate parsed data
    if (isNaN(temperature) || isNaN(humidity) || isNaN(pressure)) {
      console.error(" ERROR: Invalid sensor data received:", payload);
      return res.status(400).json({ error: "Invalid sensor values" });
    }

    // Log before inserting into the database
    console.log(` Inserting into DB → Temperature: ${temperature}, Humidity: ${humidity}, Pressure: ${pressure}`);

    // Insert into PostgreSQL
    const query = `
        INSERT INTO sensor_data (temperature, humidity, pressure, received_at)
        VALUES ($1, $2, $3, NOW()) RETURNING *;
      `;
    const values = [temperature, humidity, pressure];

    const result = await pool.query(query, values);
    console.log(" Data successfully inserted:", result.rows[0]);

    res.status(200).json({ message: "Data received successfully" });

  } catch (error) {
    console.error(" CRITICAL ERROR processing webhook:", error);
    res.status(500).json({ error: error.message || "Internal server error" });
  }
});


// API to Fetch Latest Sensor Data
app.get("/latest-data", async (req, res) => {
  try {
    const result = await pool.query("SELECT * FROM sensor_data ORDER BY received_at DESC LIMIT 1");

    if (result.rows.length === 0) {
      return res.status(404).json({ error: "No sensor data found" });
    }

    res.json(result.rows[0]);
  } catch (error) {
    res.status(500).json({ error: error.message });
  }
});

const axios = require("axios");

app.post("/send-command", async (req, res) => {
  try {
    const { command } = req.body;

    if (typeof command !== "boolean") {
      return res.status(400).json({ error: "Invalid command format. Expected boolean." });
    }

    const payload = command ? [0x01] : [0x00]; // Convert boolean to byte

    const response = await axios.post(
      TTN_API_URL,
      {
        downlinks: [
          {
            f_port: 10,
            frm_payload: Buffer.from(payload).toString("base64"),
            priority: "NORMAL",
          },
        ],
      },
      {
        headers: {
          Authorization: TTN_API_KEY,
          "Content-Type": "application/json",
        },
      }
    );

    console.log(" Pump command sent:", response.data);

    // Log pump activation in DB
    const insertQuery = "INSERT INTO pump_commands (command) VALUES ($1) RETURNING *";
    const result = await pool.query(insertQuery, [command]);

    res.status(200).json({ message: "Command sent successfully", pumpData: result.rows[0] });

  } catch (error) {
    console.error(" ERROR sending pump command:", error.response?.data || error.message);
    res.status(500).json({ error: "Failed to send command" });
  }
});


app.get("/pump-history", async (req, res) => {
  try {
    const result = await pool.query("SELECT * FROM pump_commands ORDER BY sent_at DESC LIMIT 5");
    res.json(result.rows);
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
});


// Sample API to Retrieve Alarms from DB
app.get("/api/alarms", async (req, res) => {
  try {
    const result = await pool.query("SELECT * FROM alarm");
    res.json(result.rows);
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
});

// Sample API for Water Tank Level
app.get("/watertank", (req, res) => {
  res.json({ level: 50 });
});

// Start Server
app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});
