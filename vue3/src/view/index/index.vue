<template>
  <div class="safe-box">
    <h1 class="text-center">OneLink</h1>
    <h2 class="text-center">添加支持WOL的设备</h2>

    <van-field
      v-model="deviceName"
      required
      label="设备名称"
      placeholder="请输入设备名称"
    />
    <van-field
      v-model="deviceMac"
      required
      maxlength="12"
      label="MAC地址"
      placeholder="请输入无符号MAC地址"
    />
    <van-cell center>
      <template #title>
        <span>{{ macFormatter(deviceMac) }}</span>
      </template>
    </van-cell>
    <div class="block"></div>
    <van-button type="primary" size="large" @click="addDevice"
      >添加设备</van-button
    >
    <Tabbar />
  </div>
</template>
<script setup>
import { ref } from 'vue';
import Tabbar from '@/components/tabbar/index.vue';
import localforage from 'localforage';
import { ulid } from 'ulid';
import { useRouter } from 'vue-router';
import { showDialog } from 'vant';
const router = useRouter();
const deviceName = ref('');
const deviceMac = ref('');
const addDevice = () => {
  if (!deviceName.value || !deviceMac.value) {
    return;
  }
  if (!macJudge(deviceMac.value)) {
    showDialog({ message: 'MAC地址格式不正确' });
    return;
  }
  localforage.getItem('devices').then((data) => {
    const devices = data || [];
    devices.push({
      id: ulid(),
      name: deviceName.value,
      mac: macFormatter(deviceMac.value),
    });
    localforage.setItem('devices', devices).then(() => {
      deviceName.value = '';
      deviceMac.value = '';
    });
    pushToList();
  });
};

const pushToList = () => {
  router.push({ path: '/list' });
};

const macJudge = () => {
  return !/^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$/.test(deviceMac.value);
};

const macFormatter = (value) => {
  // 格式化成大写并且符合MAC地址的格式 xx:xx:xx:xx:xx:xx
  return value
    .toUpperCase()
    .replace(/(.{2})/g, '$1:')
    .slice(0, 17);
};
</script>

<style lang="less"></style>
