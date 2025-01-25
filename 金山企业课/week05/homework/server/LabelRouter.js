const Router = require('koa-router');
const fs = require('fs/promises');
const { koaBody } = require('koa-body');

const LabelRouter = new Router();
const dataPath = 'tags.json'; // 自定义数据文件路径

// 读取标签数据
async function readTagsData() {
  try {
    const tagsData = await fs.readFile(dataPath, 'utf-8');
    return JSON.parse(tagsData);
  } catch (error) {
    console.error('Error reading tags data:', error);
    throw new Error('Unable to read tags data');
  }
}

// 写入标签数据
async function writeTagsData(tags) {
  try {
    await fs.writeFile(dataPath, JSON.stringify(tags, null, 2));
  } catch (error) {
    console.error('Error writing tags data:', error);
    throw new Error('Unable to write tags data');
  }
}

// 定义标签查询接口
LabelRouter.get('/tags', async (ctx) => {
  try {
    const tags = await readTagsData();
    ctx.body = tags;
  } catch (error) {
    ctx.status = 500;
    ctx.body = { error: 'Internal Server Error' };
  }
});

// 定义标签添加接口
LabelRouter.post('/tags',koaBody(), async (ctx) => {
  try {
    const { id, name } = ctx.request.body;
    const tags = await readTagsData();

    const newTag = { id, name };
    tags.push(newTag);

    await writeTagsData(tags);
    ctx.body = newTag;
  } catch (error) {
    ctx.status = 500;
    ctx.body = { error: 'Internal Server Error' };
  }
});

// 定义标签编辑接口
LabelRouter.put('/tags/:id',koaBody(), async (ctx) => {
  try {
    const { id } = ctx.params;
    const { name } = ctx.request.body;
    const tags = await readTagsData();

    const tagIndex = tags.findIndex(tag => tag.id === id);
    if (tagIndex === -1) {
      ctx.status = 404;
      ctx.body = { error: 'Tag not found' };
      return;
    }

    tags[tagIndex].name = name;

    await writeTagsData(tags);
    ctx.body = tags[tagIndex];
  } catch (error) {
    ctx.status = 500;
    ctx.body = { error: 'Internal Server Error' };
  }
});

// 定义标签删除接口
LabelRouter.delete('/tags/:id', async (ctx) => {
  try {
    const { id } = ctx.params;
    const tags = await readTagsData();

    const tagIndex = tags.findIndex(tag => tag.id === id);
    if (tagIndex === -1) {
      ctx.status = 404;
      ctx.body = { error: 'Tag not found' };
      return;
    }

    const deletedTag = tags.splice(tagIndex, 1)[0];

    await writeTagsData(tags);
    ctx.body = { message: 'Tag deleted', deletedTag };
  } catch (error) {
    ctx.status = 500;
    ctx.body = { error: 'Internal Server Error' };
  }
});

module.exports = LabelRouter;