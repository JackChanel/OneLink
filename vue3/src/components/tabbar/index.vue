<template>
  <van-tabbar route v-model="active" @change="onChange" placeholder>
    <van-tabbar-item replace to="/" icon="add-o" name="index"
      >添加</van-tabbar-item
    >
    <van-tabbar-item replace to="/list" icon="todo-list-o" name="list"
      >历史</van-tabbar-item
    >
  </van-tabbar>
</template>
<script setup></script>
