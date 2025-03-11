<template>
  <div class="safe-box">
    <h2 class="text-center">设备列表</h2>
    <Empty v-if="!hasDevices" description="" />
    <van-cell-group v-else>
      <van-cell center v-for="device in devices" :key="device.id">
        <template #title>
          <van-icon name="desktop-o" style="margin-right: 5px" />
          <span>{{ device.name }}</span>
          <div>
            <span>Mac: {{ device.mac }}</span>
          </div>
        </template>
        <template #right-icon>
          <van-button
            type="danger"
            size="small"
            style="margin-right: 10px"
            @click="deleteDevice(device.id)"
            >删除</van-button
          >
          <van-button type="success" size="small" @click="onWake(device.mac)"
            >唤醒</van-button
          >
        </template>
      </van-cell>
    </van-cell-group>
    <Tabbar />
  </div>
</template>
<script setup>
import { ref } from 'vue';
import { Empty, showDialog, showNotify } from 'vant';
import service from '../../utils/axios';
import 'vant/es/dialog/style';
import 'vant/es/notify/style';
import localforage from 'localforage';

const devices = ref([]);
const hasDevices = ref(false);
localforage.getItem('devices').then((data) => {
  devices.value = data || [];
  hasDevices.value = devices.value.length > 0;
});
const deleteDevice = (id) => {
  showDialog({
    title: '提示',
    message: '确定删除该设备吗？',
    showCancelButton: true,
  })
    .then(() => {
      localforage.getItem('devices').then((data) => {
        const forage_devices = data || [];
        const new_devices = forage_devices.filter((device) => device.id !== id);
        localforage.setItem('devices', new_devices).then(() => {
          devices.value = new_devices;
          hasDevices.value = devices.value.length > 0;
        });
        devices.value = new_devices;
      });
    })
    .catch(() => {});
};
const onWake = (macAddress) => {
  service.get('/wol', { params: { mac: macAddress } }).then((res) => {
    const { code, msg } = res;
    if (code === 200) {
      showNotify({ type: 'success', message: msg });
    } else {
      showNotify({ type: 'danger', message: msg });
    }
  });
};
</script>
