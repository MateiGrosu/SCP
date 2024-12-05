import React, { useState, useEffect } from "react";
import axios from "axios";

const WaterTank = () => {
  const [level, setLevel] = useState(0); // Initial water level
  const [loading, setLoading] = useState(true); // Loading state
  const [error, setError] = useState(null); // Error state
  const apiUrl = "http://localhost:5001/watertank"; // Hardcoded API URL

  useEffect(() => {
    const fetchWaterLevel = async () => {
      try {
        setLoading(true);
        setError(null);

        // Using Axios for the HTTP request
        const response = await axios.get(apiUrl);

        // Assume backend sends: { level: number }
        setLevel(response.data.level);
      } catch (err) {
        setError(err.message || "An error occurred");
      } finally {
        setLoading(false);
      }
    };

    // Fetch water level on component mount
    fetchWaterLevel();

    // Optional: Poll the API every 5 seconds
    const interval = setInterval(fetchWaterLevel, 5000);

    // Cleanup interval on unmount
    return () => clearInterval(interval);
  }, [apiUrl]);

  if (loading) {
    return <p>Loading water level...</p>;
  }

  if (error) {
    return <p style={{ color: "red" }}>Error: {error}</p>;
  }

  const waterLevel = Math.min(100, Math.max(0, level)); // Ensure level is within 0-100%

  return (
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
  );
};

const styles = {
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
};

export default WaterTank;