import axios from 'axios';

async function getTags(){
    try {
      const response = await axios.get('/tags');
      return response.data;
    } catch (error) {
      throw new Error(error.response.data.error);
    }
  };

async function addTag(id, name){
try {
    const response = await axios.post('/tags', { id, name });
    return response.data;
    } catch (error) {
    throw new Error(error.response.data.error);
    }
}
  async function editTag (id, name){
    try {
      const response = await axios.put(`/tags/${id}`, { name });
      return response.data;
    } catch (error) {
      throw new Error(error.response.data.error);
    }
  };
  
  async function deleteTag (id) {
    try {
      const response = await axios.delete(`/tags/${id}`);
      return response.data.deletedTag;
    } catch (error) {
      throw new Error(error.response.data.error);
    }
  };

  export { getTags, addTag, editTag, deleteTag };