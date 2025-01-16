import React, { useState, useEffect } from "react";
import axios from "axios";
import { Button, Table, TableBody, TableCell, TableContainer, TableHead, TableRow, Paper } from "@mui/material";
import AlarmRow from "./AlarmRow";
import AlarmDialog from "./AlarmDialog";

const AlarmTable = () => {
  const [alarms, setAlarms] = useState([]);
  const [openDialog, setOpenDialog] = useState(false);
  const [alarmToEdit, setAlarmToEdit] = useState(null);

  // Fetch alarms when the component mounts
  useEffect(() => {
    const fetchAlarms = async () => {
      try {
        const response = await axios.get("http://localhost:5001/api/alarms");
        setAlarms(response.data);
      } catch (error) {
        console.error("Error fetching alarms:", error);
      }
    };

    fetchAlarms();
  }, []);

  const handleAddClick = () => {
    setAlarmToEdit(null); // For a new alarm, reset the edit state
    setOpenDialog(true); // Open the dialog for adding a new alarm
  };

  const handleEditClick = (alarm) => {
    setAlarmToEdit(alarm); // Set the alarm to edit
    setOpenDialog(true); // Open the dialog for editing
  };

  const handleDialogClose = () => {
    setOpenDialog(false); // Close the dialog
    setAlarmToEdit(null); // Clear the alarm to edit when dialog closes
  };

  const handleSaveAlarm = (updatedAlarm) => {
    if (updatedAlarm.id) {
      // Edit existing alarm
      setAlarms(alarms.map((alarm) => (alarm.id === updatedAlarm.id ? updatedAlarm : alarm)));
    } else {
      // Add new alarm
      setAlarms([...alarms, updatedAlarm]);
    }
    setOpenDialog(false); // Close the dialog after saving
  };

  return (
    <div>
      {/* Add Alarm Button */}
      <Button variant="contained" color="primary" onClick={handleAddClick} className="mb-4">
        Add Alarm
      </Button>

      {/* Alarm Table */}
      <TableContainer component={Paper} className="shadow-lg rounded-lg mt-4">
        <Table>
          <TableHead className="bg-blue-500">
            <TableRow>
              <TableCell className="text-white font-bold">Time</TableCell>
              <TableCell className="text-white font-bold">Label</TableCell>
              <TableCell className="text-white font-bold">Snooze</TableCell>
              <TableCell className="text-white font-bold">Spray lvl</TableCell>
              <TableCell className="text-white font-bold"></TableCell>
            </TableRow>
          </TableHead>
          <TableBody>
            {alarms.map((alarm) => (
              <AlarmRow 
                key={alarm.id} 
                alarm={alarm} 
                onEdit={handleEditClick} 
              />
            ))}
          </TableBody>
        </Table>
      </TableContainer>

      {/* Alarm Dialog */}
      <AlarmDialog
        open={openDialog}
        alarm={alarmToEdit}
        onClose={handleDialogClose}
        onSave={handleSaveAlarm}
      />
    </div>
  );
};

export default AlarmTable;