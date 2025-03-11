<template>
  <div id="app">
    <router-view />
  </div>
  <Tabbar />
</template>
<script setup>
import Tabbar from '@/components/tabbar/index.vue';
</script>
<style>
body {
  font-size: 16px;
  background-color: #f8f8f8;
  -webkit-font-smoothing: antialiased;
}
.text-center {
  text-align: center;
}
.safe-box {
  padding: 20px;
  background-color: #fff;
  box-shadow: 0 2px 4px 0 rgba(0, 0, 0, 0.1);
}
.block {
  margin-top: 20px;
}
</style>
