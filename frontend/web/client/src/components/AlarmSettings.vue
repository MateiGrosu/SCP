<script setup lang="js">
import { ref } from 'vue'

const spraySpeed = ref(0)
const alarmDelay = ref(0)
</script>

<template>
    <div id="app">
        <h3>Alarm Clock Settings</h3>
        <label>
            Water Spray Speed:
            <input type="range"  v-model="spraySpeed" min="1" max="10" />
            {{ spraySpeed }}
        </label>
        <br>
        <label>
            Alarm Delay:
            <input type="number" class="alarmDelay" v-model="alarmDelay" min="0" /> seconds
        </label>
        <br>
        <button @click="sendSettings">Save Settings</button>
    </div>
</template>

<style scoped>
label {
    display: block;
    font-weight: bold;
    margin-bottom: 5px;
}

.alarmDelay{
    width: 50px;
}

button {
    padding: 10px 15px;
    background-color: #3498db;
    color: #fff;
    border: none;
    border-radius: 5px;
    cursor: pointer;
}

button:hover {
    background-color: #2980b9;
}
</style>