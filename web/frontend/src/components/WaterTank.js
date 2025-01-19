import React, { useState, useEffect } from "react";
import axios from "axios";

const WaterTank = () => {
  const [level, setLevel] = useState(0); // Initial water level
  const [loading, setLoading] = useState(true); // Loading state
  const [error, setError] = useState(null); // Error state
  const [isPumpOn, setIsPumpOn] = useState(false); // Track pump state
  const apiUrl = "https://backend-alarm.onrender.com/watertank"; // API to fetch water level
  const pumpApiUrl = "https://backend-alarm.onrender.com/send-command"; // API to control the pump

  useEffect(() => {
    const fetchWaterLevel = async () => {
      try {
        setLoading(true);
        setError(null);

        const response = await axios.get(apiUrl);

        setLevel(response.data.level);
      } catch (err) {
        setError(err.message || "An error occurred");
      } finally {
        setLoading(false);
      }
    };

    // Fetch water level on component mount
    fetchWaterLevel();

    // Poll the API every 50 seconds
    const interval = setInterval(fetchWaterLevel, 50000);

    return () => clearInterval(interval);
  }, [apiUrl]);

  // Function to send pump control command
  const togglePump = async () => {
    try {
      const response = await axios.post(pumpApiUrl, {
        command: !isPumpOn, // Send the opposite state to toggle
      });

      if (response.status === 200) {
        setIsPumpOn(!isPumpOn); // Toggle pump state in UI
      }
    } catch (err) {
      console.error("Error sending pump command:", err);
      setError("Failed to send pump command");
    }
  };

  if (loading) {
    return <p>Loading water level...</p>;
  }

  if (error) {
    return <p style={{ color: "red" }}>Error: {error}</p>;
  }

  const waterLevel = Math.min(100, Math.max(0, level)); // Ensure level is within 0-100%

  return (
    <div style={styles.container}>
      <div style={styles.tankContainer}>
        <div style={styles.tank}>
          <div
            style={{
              ...styles.water,
              height: `${waterLevel}%`,
            }}
          />
          <div style={styles.text}>{waterLevel}%</div>
        </div>
      </div>
      <button onClick={togglePump} style={styles.pumpButton}>
        {isPumpOn ? "Turn Pump OFF" : "Turn Pump ON"}
      </button>
    </div>
  );
};

const styles = {
  container: {
    textAlign: "center",
    padding: "20px",
  },
  tankContainer: {
    display: "flex",
    justifyContent: "center",
    alignItems: "center",
    margin: "20px 0",
  },
  tank: {
    position: "relative",
    width: "100px",
    height: "200px",
    border: "2px solid #4a90e2",
    borderRadius: "10px",
    overflow: "hidden",
    backgroundColor: "#f1f1f1",
  },
  water: {
    position: "absolute",
    bottom: 0,
    width: "100%",
    backgroundColor: "#4a90e2",
    transition: "height 0.5s ease",
  },
  text: {
    position: "absolute",
    width: "100%",
    top: "50%",
    transform: "translateY(-50%)",
    textAlign: "center",
    fontWeight: "bold",
    color: "#333",
    fontSize: "18px",
  },
  pumpButton: {
    padding: "10px 20px",
    fontSize: "16px",
    backgroundColor: "#28a745",
    color: "#fff",
    border: "none",
    borderRadius: "5px",
    cursor: "pointer",
    marginTop: "20px",
  },
};

export default WaterTank;
