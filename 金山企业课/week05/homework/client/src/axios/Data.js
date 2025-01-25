import axios from 'axios';

// 查询数据接口
async function fetchData(query) {
  try {
    const response = await axios.get('/data', { params: query });
    return response.data;
  } catch (error) {
    throw new Error('Failed to fetch data');
  }
}

// 添加数据接口
async function addData(data) {
  try {
    const response = await axios.post('/data', data);
    return response.data;
  } catch (error) {
    throw new Error('Failed to add data');
  }
}

// 编辑数据接口
async function editData(id, data) {
  try {
    const response = await axios.put(`/data/${id}`, data);
    return response.data;
  } catch (error) {
    throw new Error('Failed to edit data');
  }
}

// 删除数据接口
async function deleteData(id) {
  try {
    const response = await axios.delete(`/data/${id}`);
    return response.data;
  } catch (error) {
    throw new Error('Failed to delete data');
  }
}

export { fetchData, addData, editData, deleteData };