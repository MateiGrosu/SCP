<template>
    <div class="digital-clock">
        <div class="card">
            <p class="time-part">{{ hours }}</p>
            <p class="label">Hours</p>
        </div>
        <div class="card">
            <p class="time-part">{{ minutes }}</p>
            <p class="label">Minutes</p>
        </div>
        <div class="card">
            <p class="time-part">{{ seconds }}</p>
            <p class="label">Seconds</p>
        </div>
    </div>
</template>

<script>
export default {
    name: 'DigitalClock',
    data() {
        return { currentTime: new Date(), };
    },
    computed: {
        hours() { return String(this.currentTime.getHours()).padStart(2, '0'); },
        minutes() { return String(this.currentTime.getMinutes()).padStart(2, '0'); },
        seconds() { return String(this.currentTime.getSeconds()).padStart(2, '0'); },
    },
    mounted() {
        this.timer = setInterval(() => { this.currentTime = new Date(); }, 1000);
    },
    beforeUnmount() {
        clearInterval(this.timer);
    },
};
</script>

<style scoped>
.digital-clock {
    display: flex;
    gap: 10px;
    justify-content: center;
    align-items: center;
}

.card {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    background-color: #2c3e50;
    border-radius: 12px;
    /* Card shape, adjust for different shapes */
    padding: 20px;
    width: 80px;
    height: 100px;
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
}

.time-part {
    font-size: 2em;
    color: #00ffcc;
    margin: 0;
}

.label {
    font-size: 0.8em;
    color: #ecf0f1;
    text-transform: uppercase;
    margin-top: 8px;
}
</style>