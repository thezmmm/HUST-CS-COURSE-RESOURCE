const Router = require('koa-router');
const fs = require('fs/promises');
const { v4: uuidv4 } = require('uuid');
const { koaBody } = require('koa-body');

const router = new Router();

const dataFilePath = './data.json';

// 查询数据接口
router.get('/data', async (ctx) => {
  try {
    const { query } = ctx.request;
    const data = await readDataFromFile();

    // 判断查询参数是否为空
    if (Object.keys(query).length === 0) {
      ctx.body = data;
      return;
    }

    // 根据查询参数过滤数据
    const filteredData = data.filter((item) => {
      let match = true;
      for (const key in query) {
        if (key === 'selectedTime') {
          const selectedTime = query[key];
          const currentTime = new Date();

          if (selectedTime === 'today') {
            const itemTime = new Date(item.time);
            if (!isSameDay(itemTime, currentTime)) {
              match = false;
              break;
            }
          } else if (selectedTime === 'yesterday') {
            const itemTime = new Date(item.time);
            const yesterday = new Date();
            yesterday.setDate(currentTime.getDate() - 1);
            if (!isSameDay(itemTime, yesterday)) {
              match = false;
              break;
            }
          } else if (selectedTime === 'this_week') {
            const itemTime = new Date(item.time);
            if (!isSameWeek(itemTime, currentTime)) {
              match = false;
              break;
            }
          } else if (selectedTime === 'this_month') {
            const itemTime = new Date(item.time);
            if (!isSameMonth(itemTime, currentTime)) {
              match = false;
              break;
            }
          }
        } else {
          // 判断字段内容是否为空字符串
          if (query[key] !== '' && item[key] !== query[key]) {
            match = false;
            break;
          }
        }
      }
      return match;
    });

    ctx.body = filteredData;
  } catch (error) {
    ctx.status = 500;
    ctx.body = { error: 'Internal Server Error' };
  }
});

// 判断两个日期是否是同一天
function isSameDay(date1, date2) {
  return (
    date1.getFullYear() === date2.getFullYear() &&
    date1.getMonth() === date2.getMonth() &&
    date1.getDate() === date2.getDate()
  );
}

// 判断两个日期是否是同一周
function isSameWeek(date1, date2) {
  const date1Week = getWeekNumber(date1);
  const date2Week = getWeekNumber(date2);
  return (
    date1.getFullYear() === date2.getFullYear() &&
    date1Week === date2Week
  );
}

// 获取日期所在的周数
function getWeekNumber(date) {
  const firstDayOfYear = new Date(date.getFullYear(), 0, 1);
  const pastDaysOfYear = (date - firstDayOfYear) / 86400000;
  return Math.ceil((pastDaysOfYear + firstDayOfYear.getDay() + 1) / 7);
}

// 判断两个日期是否是同一个月
function isSameMonth(date1, date2) {
  return (
    date1.getFullYear() === date2.getFullYear() &&
    date1.getMonth() === date2.getMonth()
  );
}

// 添加数据接口
router.post('/data',koaBody(), async (ctx) => {
  try {
    const { name, description, time, tagId } = ctx.request.body;
    
    const data = await readDataFromFile();
    const newData = {
      id: uuidv4().slice(0, 5),
      name,
      description,
      time,
      tagId
    };
    data.push(newData);
    await writeDataToFile(data);

    ctx.body = newData;
    ctx.status = 201; // Created
  } catch (error) {
    ctx.status = 500;
    ctx.body = { error: 'Internal Server Error' };
  }
});

// 编辑数据接口
router.put('/data/:id',koaBody(), async (ctx) => {
  try {
    const { id } = ctx.params;
    const { name, description, time, tagId } = ctx.request.body;
    const data = await readDataFromFile();

    const dataIndex = data.findIndex((item) => item.id === id);
    if (dataIndex === -1) {
      ctx.status = 404;
      ctx.body = { error: 'Data not found' };
      return;
    }

    data[dataIndex] = {
      id,
      name,
      description,
      time,
      tagId
    };

    await writeDataToFile(data);

    ctx.body = data[dataIndex];
    ctx.status = 200; // OK
  } catch (error) {
    ctx.status = 500;
    ctx.body = { error: 'Internal Server Error' };
  }
});

// 删除数据接口
router.del('/data/:id', async (ctx) => {
  try {
    const { id } = ctx.params;
    let data = await readDataFromFile();

    const dataIndex = data.findIndex((item) => item.id === id);
    if (dataIndex === -1) {
      ctx.status = 404;
      ctx.body = { error: 'Data not found' };
      return;
    }

    data = data.filter((item) => item.id !== id);
    await writeDataToFile(data);

    ctx.body = { message: 'Data deleted successfully' };
    ctx.status = 200; // OK
  } catch (error) {
    ctx.status = 500;
    ctx.body = { error: 'Internal Server Error' };
  }
});

// 从 JSON 文件中读取数据
async function readDataFromFile() {
  const data = await fs.readFile(dataFilePath, 'utf-8');
  return JSON.parse(data);
}

// 将数据写入 JSON 文件
async function writeDataToFile(data) {
  await fs.writeFile(dataFilePath, JSON.stringify(data, null, 2), 'utf-8');
}

module.exports = router;