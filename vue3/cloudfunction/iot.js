const iot = require('alibabacloud-iot-device-sdk');

const MQTTClient = iot.device({
  // 设备三元组
  productKey: 'a1TcFhbvXev',
  deviceName: 'application',
  deviceSecret: '6dd800506e895e71bdf30fc85d2216d8',

  // MQTT连接设置
  brokerUrl: 'mqtt://a1TcFhbvXev.iot-as-mqtt.cn-shanghai.aliyuncs.com',
  regionId: 'cn-shanghai',
  keepalive: 60,
});

const MQTTStatus = {
  connected: false,
};

const topic = {
  // 订阅主题
  sub: '/sys/a1TcFhbvXev/application/thing/service/property/set',
  // 发布主题
  pub: '/sys/a1TcFhbvXev/application/thing/event/property/post',
};

MQTTClient.on('connect', () => {
  console.log('connect successfully!');
  MQTTStatus.connected = true;
  // 订阅主题
  MQTTClient.subscribe(topic.sub);
});

const sendWOL = (MACAddress) => {
  MQTTClient.publish(
    topic.pub,
    JSON.stringify({
      id: 'RUNING',
      version: '1.0',
      params: { ESPSTATUS: 1, MACAddress },
      method: 'thing.event.property.post',
    })
  );
};

module.exports = {
  MQTTStatus,
  sendWOL,
};
