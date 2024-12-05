import React, { useState, useEffect } from "react";
import {
  Dialog,
  DialogActions,
  DialogContent,
  DialogTitle,
  Button,
  TextField,
  Select,
  MenuItem,
  FormControl,
  InputLabel,
  Slider,
  Switch,
  FormControlLabel,
} from "@mui/material";

const AlarmDialog = ({ open, alarm, onClose, onSave }) => {
  const [newAlarm, setNewAlarm] = useState({
    time: "",
    label: "",
    repeat: "none",
    snoozeTime: 5, // Default snooze time in minutes
    waterSprayLvl: 0, // Default water spray intensity
    led: false, // Default LED state
  });

  useEffect(() => {
    if (alarm) {
      setNewAlarm({
        ...alarm,
        snoozeTime: alarm.snoozeTime || 5,
        waterSprayLvl: alarm.waterSprayLvl || 0,
        led: alarm.led || false,
      });
    }
  }, [alarm]);

  const handleSliderChange = (field) => (event, newValue) => {
    setNewAlarm((prev) => ({ ...prev, [field]: newValue }));
  };

  const handleToggleChange = (event) => {
    setNewAlarm((prev) => ({ ...prev, led: event.target.checked }));
  };

  const handleSave = () => {
    if (!newAlarm.time || !newAlarm.label) {
      alert("Please fill in both fields.");
      return;
    }
    onSave(newAlarm); // Pass the new or edited alarm to the parent
  };

  return (
    <Dialog open={open} onClose={onClose}>
      <DialogTitle>{alarm ? "Edit Alarm" : "Add New Alarm"}</DialogTitle>
      <DialogContent>
        <TextField
          type="time"
          label="Alarm Time"
          fullWidth
          value={newAlarm.time}
          onChange={(e) => setNewAlarm({ ...newAlarm, time: e.target.value })}
          margin="dense"
        />
        <TextField
          label="Alarm Label"
          fullWidth
          value={newAlarm.label}
          onChange={(e) => setNewAlarm({ ...newAlarm, label: e.target.value })}
          margin="dense"
        />
        <FormControl fullWidth margin="dense">
          <InputLabel>Repeat</InputLabel>
          <Select
            value={newAlarm.repeat}
            onChange={(e) =>
              setNewAlarm({ ...newAlarm, repeat: e.target.value })
            }
          >
            <MenuItem value="none">None</MenuItem>
            <MenuItem value="daily">Daily</MenuItem>
            <MenuItem value="weekly">Weekly</MenuItem>
          </Select>
        </FormControl>
        <FormControl fullWidth margin="dense">
          <p>Snooze Duration (minutes):</p>
          <Slider
            value={newAlarm.snoozeTime}
            onChange={handleSliderChange("snoozeTime")}
            min={1}
            max={30}
            step={1}
            marks
            valueLabelDisplay="auto"
            aria-label="Snooze Time"
          />
        </FormControl>
        <FormControl fullWidth margin="dense">
          <p>Water Spray Intensity (0-100):</p>
          <Slider
            value={newAlarm.waterSprayLvl}
            onChange={handleSliderChange("waterSprayLvl")}
            min={0}
            max={100}
            step={10}
            marks
            valueLabelDisplay="auto"
            aria-label="Water Spray Intensity"
          />
        </FormControl>
        <FormControlLabel
          label="LED On/Off"
          control={
            <Switch
              checked={newAlarm.led}
              onChange={handleToggleChange}
              color="primary"
            />
          }
        />
      </DialogContent>
      <DialogActions>
        <Button onClick={onClose} color="secondary">
          Cancel
        </Button>
        <Button onClick={handleSave} color="primary">
          Save
        </Button>
      </DialogActions>
    </Dialog>
  );
};

export default AlarmDialog;