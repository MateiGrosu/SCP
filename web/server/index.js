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

app.use(cors({
  origin: ["http://localhost:3000", "https://frontend-alarm.onrender.com"]
}));
app.use(express.json()); // Parse JSON request bodies

app.get("/", (req, res) => {
  res.send("Welcome to the backend server!");
});

//  API Endpoint to Receive TTN Webhook Data
app.post("/temperature", async (req, res) => {
  try {
    console.log("Received TTN Data:", JSON.stringify(req.body, null, 2));

    const uplinkMessage = req.body.uplink_message;
    if (!uplinkMessage) {
      return res.status(400).json({ error: "Invalid payload: Missing uplink_message" });
    }

    // Extract sensor data
    const payload = uplinkMessage.decoded_payload;
    const temperature = parseFloat(payload.temperature);
    const humidity = parseFloat(payload.humidity);
    const pressure = parseFloat(payload.pressure);

    // Store sensor data in PostgreSQL
    const query = `
      INSERT INTO sensor_data (temperature, humidity, pressure, received_at)
      VALUES ($1, $2, $3, NOW()) RETURNING *;
    `;
    const values = [temperature, humidity, pressure];

    const result = await pool.query(query, values);
    console.log("Data inserted:", result.rows[0]);

    res.status(200).json({ message: "Data received successfully" });
  } catch (error) {
    console.error("Error processing webhook:", error);
    res.status(500).json({ error: error.message });
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
