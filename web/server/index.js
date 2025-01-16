const express = require('express');
const cors = require('cors');
const { Pool } = require('pg');
require('dotenv').config();

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
  origin: ['http://localhost:3000', 'https://frontend-alarm.onrender.com']
}));
app.use(express.json()); // Parse JSON request bodies

app.get('/', (req, res) => {
  res.send('Welcome to the backend server!');
});

// Sample API endpoint
app.get('/api/data', (req, res) => {
  res.json({ message: 'Hello from the backend!' });
});

app.get("/api/alarms", async (req, res) => {
  try {
    const alarms = await getAllAlarms();
    res.json(alarms);
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
});

async function getAllAlarms() {
  try {
    const result = await pool.query('SELECT * FROM alarm');
    return result.rows;
  } catch (err) {
    throw new Error(err.message);
  }
}

app.get("/watertank", (req, res) => {
  res.json({ level: 50 });
});

app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});