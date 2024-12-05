import React from "react";
import { Button, TableCell, TableRow } from "@mui/material";

const AlarmRow = ({ alarm, onEdit }) => {
  return (
    <TableRow className="hover:bg-gray-100">
      <TableCell className="text-gray-700">{alarm.time}</TableCell>
      <TableCell className="text-gray-700">{alarm.label}</TableCell>
      <TableCell className="text-gray-700">{alarm.repeat}</TableCell>
      <TableCell className="text-gray-700">{alarm.snoozeTime} min</TableCell>
      <TableCell className="text-gray-700">{alarm.waterSprayLvl}</TableCell>
      <TableCell className="text-gray-700">{alarm.led}</TableCell>
      <TableCell className="text-gray-700">
        <Button variant="outlined" color="primary" onClick={() => onEdit(alarm)}>
          Edit
        </Button>
      </TableCell>
    </TableRow>
  );
};

export default AlarmRow;