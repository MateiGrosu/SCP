const express = require('express');
const cors = require('cors');

const app = express();
const PORT = process.env.PORT || 5001;

app.use(cors({
  origin: 'http://localhost:3000'
}));
app.use(express.json()); // Parse JSON request bodies

// Sample API endpoint
app.get('/api/data', (req, res) => {
  res.json({ message: 'Hello from the backend!' });
});

let alarms = [];

app.post("/alarms", (req, res) => {
  const { time, label } = req.body;
  if (!time || !label) {
    return res.status(400).json({ error: "Time and label are required." });
  }

  const newAlarm = { id: alarms.length + 1, time, label };
  alarms.push(newAlarm);
  res.status(201).json(newAlarm);
});

app.put("/alarms/:id", (req, res) => {
  const { id } = req.params;
  const { time, label } = req.body;
  const alarmIndex = alarms.findIndex((alarm) => alarm.id === parseInt(id));

  if (alarmIndex === -1) {
    return res.status(404).json({ error: "Alarm not found." });
  }

  if (!time || !label) {
    return res.status(400).json({ error: "Time and label are required." });
  }

  const updatedAlarm = { ...alarms[alarmIndex], time, label };
  alarms[alarmIndex] = updatedAlarm;
  res.json(updatedAlarm);
});

app.get("/alarms", (req, res) => {
  res.json(alarms);
});

app.get("/watertank", (req, res) => {
  res.json({ level: 50 });
});

app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});