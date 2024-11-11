<template>
    <div>
      <h1>{{ message }}</h1>
    </div>
  </template>
  
  <script>
  export default {
    data() {
      return {
        message: '',
      };
    },
    created() {
      this.fetchData();
    },
    methods: {
      async fetchData() {
        try {
          const response = await fetch('/api/data');
          if (!response.ok) throw new Error('Network response was not ok');
          const data = await response.json();
          this.message = data.message;
        } catch (error) {
          console.error('Error fetching data:', error);
        }
      },
    },
  };
  </script>