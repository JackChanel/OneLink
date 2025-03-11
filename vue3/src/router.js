import { createRouter, createWebHashHistory } from 'vue-router';

const routes = [
  {
    name: 'notFound',
    path: '/:path(.*)+',
    redirect: {
      name: 'index',
    },
  },
  {
    name: 'index',
    path: '/',
    component: () => import('./view/index'),
    meta: {
      title: '首页',
    },
  },
  {
    name: 'list',
    path: '/list',
    component: () => import('./view/list'),
    meta: {
      title: '列表',
    },
  },
];

const router = createRouter({
  routes,
  history: createWebHashHistory(),
});

router.beforeEach((to, from, next) => {
  const title = to.meta && to.meta.title;
  if (title) {
    document.title = title;
  }
  next();
});

export { router };
