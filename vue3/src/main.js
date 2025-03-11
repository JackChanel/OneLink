import { createApp } from 'vue';
import { Tabbar, TabbarItem } from 'vant';
import App from './App.vue';
import { router } from './router';
import { Dialog } from 'vant';

const app = createApp(App);
app.use(router);
app.use(Tabbar);
app.use(Dialog);
app.use(TabbarItem);
app.mount('#app');
