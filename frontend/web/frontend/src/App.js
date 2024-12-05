import './App.css';
import AlarmTable from './components/AlarmTable';
import Clock from './components/Clock';
import WaterTank from './components/WaterTank';

function App() {

  return (
    <div className="flex flex-col">
      <div className="flex-1 items-center justify-center  bg-gray-100">
        <Clock />
      </div>
      <div className="flex justify-center pt-3">
        <AlarmTable />
        <WaterTank />
        </div>

    </div>
  );
}

export default App;
