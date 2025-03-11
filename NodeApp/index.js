const iot = require("alibabacloud-iot-device-sdk");

const MQTTClient = iot.device({
  // 设备三元组
  productKey: "a1TcFhbvXev",
  deviceName: "application",
  deviceSecret: "6dd800506e895e71bdf30fc85d2216d8",

  // MQTT连接设置
  brokerUrl: "mqtt://a1TcFhbvXev.iot-as-mqtt.cn-shanghai.aliyuncs.com",
  regionId: "cn-shanghai",
  keepalive: 60,
});

const topic = {
  // 订阅主题
  sub: "/sys/a1TcFhbvXev/application/thing/service/property/set",
  // 发布主题
  pub: "/sys/a1TcFhbvXev/application/thing/event/property/post",
};

MQTTClient.on("connect", () => {
  console.log("connect successfully!");
  // 订阅主题
  MQTTClient.subscribe(topic.sub);

  let count = 0;
  // 发布消息
  setInterval(() => {
    MQTTClient.publish(
      topic.pub,
      JSON.stringify({
        id: "RUNING",
        version: "1.0",
        // B2-C3-E1-1C-14-43
        params: { ESPSTATUS: 1, MACAddress: "B2:C3:E1:1C:14:43" },
        method: "thing.event.property.post",
      })
    );
  }, 6000);
});
