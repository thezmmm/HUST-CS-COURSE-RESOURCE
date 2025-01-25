const Koa = require('koa');
const router = require('./DataRouter');
const LabelRouter = require('./LabelRouter');
const serve = require('koa-static');

const app = new Koa();

app.use(serve('../client/build'));

app.use(router.routes());
app.use(LabelRouter.routes());
app.use(router.allowedMethods());
app.use(LabelRouter.allowedMethods());


app.listen(3001, () => {
  console.log('Server is running on port 3001');
});