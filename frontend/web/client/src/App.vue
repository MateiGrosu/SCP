<template>

  <HelloWorld msg="Vite + Vue" />
  <DigitalClock />
  <AlarmSettings />
  <ApiComponent />
  <NewAlarm  />
</template>


<script setup>
import { ref } from 'vue';
import AlarmSettings from './components/AlarmSettings.vue';
import ApiComponent from './components/ApiComponent.vue';
import DigitalClock from './components/DigitalClock.vue';
import HelloWorld from './components/HelloWorld.vue'
import NewAlarm from './components/NewAlarm.vue';

</script>

<style scoped>

</style>
