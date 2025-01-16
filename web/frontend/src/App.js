import './App.css';
import AlarmTable from './components/AlarmTable';
import Clock from './components/Clock';
import WaterTank from './components/WaterTank';
import WeatherInfo from './components/WeatherInfo'; // Import the new component

function App() {

  return (
    <div className="flex flex-col">
      <div className="flex-1 items-center justify-center bg-gray-100">
        <Clock />
      </div>
      <div className="flex justify-center pt-3">
        <div className="mr-4">
          <WeatherInfo />
        </div>
        <div className="mr-4">
          <AlarmTable />
        </div>
        <WaterTank />
      </div>
    </div>
  );
}

export default App;
