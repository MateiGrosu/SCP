<script setup>
import AlarmSettings from './components/AlarmSettings.vue';
import ApiComponent from './components/ApiComponent.vue';
import DigitalClock from './components/DigitalClock.vue';
import HelloWorld from './components/HelloWorld.vue'
</script>

<template>

  <HelloWorld msg="Vite + Vue" />
  <DigitalClock/>
  <AlarmSettings/>
  <ApiComponent />
</template>

<style scoped>
.logo {
  height: 6em;
  padding: 1.5em;
  will-change: filter;
  transition: filter 300ms;
}
.logo:hover {
  filter: drop-shadow(0 0 2em #646cffaa);
}
.logo.vue:hover {
  filter: drop-shadow(0 0 2em #42b883aa);
}
</style>
