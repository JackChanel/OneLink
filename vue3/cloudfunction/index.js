const express = require('express');
const bodyParser = require('body-parser');
const app = express();
const { sendWOL, MQTTStatus } = require('./iot.js');

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());
app.use(bodyParser.text());
app.use(bodyParser.raw());

app.get('/', (req, res) => {
  res.send('Hello World!');
});

app.get('/wol', (req, res) => {
  if (MQTTStatus.connected) {
    sendWOL(req.query.mac);
    res.send({ msg: '已经向MAC地址：' + req.query.mac + '发送WOL广播' });
  } else {
    res.send({ msg: 'MQTT连接未建立，无法发送WOL广播' });
  }
});

app.all('/*', (req, res) => {
  const requestId = req.headers['x-fc-request-id'];
  console.log('FC Invoke Start RequestId: ' + requestId);

  res.send(
    JSON.stringify({
      msg: 'Hello, World! ',
      reqeust: {
        query: req.query,
        path: req.originalUrl,
        data: req.body,
        clientIp: req.headers['x-forwarded-for'],
      },
    })
  );

  console.log('FC Invoke End RequestId: ' + requestId);
});

app.listen(9000, () => {
  console.log('Express started on port 9000');
});
