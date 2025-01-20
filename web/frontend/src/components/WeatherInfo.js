import React, { useState, useEffect } from "react";
import axios from "axios";

const WeatherInfo = () => {
  const [weatherData, setWeatherData] = useState({ temperature: "", humidity: "", pressure: "" });

  useEffect(() => {
    const fetchWeatherData = async () => {
      try {
        const response = await axios.get("https://backend-alarm.onrender.com/latest-data");
        setWeatherData(response.data);
      } catch (error) {
        console.error("Error fetching weather data:", error);
      }
    };

    fetchWeatherData();
    const intervalId = setInterval(fetchWeatherData, 50000); // Fetch data every 50 seconds

    return () => clearInterval(intervalId); // Cleanup interval on component unmount
  }, []);

  return (
    <div className="p-4 bg-white shadow-lg rounded-lg">
      <h2 className="text-xl font-bold mb-2">Room Information</h2>
      <p>Temperature: {weatherData.temperature} °C</p>
      <p>Humidity: {weatherData.humidity} %</p>
      <p>Pressure: {weatherData.pressure} hPa</p>
      <p>Time: {weatherData.received_at} hPa</p>
    </div>
  );
};

export default WeatherInfo;
