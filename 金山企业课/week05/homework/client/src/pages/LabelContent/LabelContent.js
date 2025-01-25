import React, { useState,useEffect } from 'react';
import Modal from 'react-modal';
import './LabelContent.css';
import { getText } from '../../redux/i18n';
import { connect } from 'react-redux';
import { getTags } from '../../axios/Label';
import { editTag,deleteTag,addTag } from '../../axios/Label';

const LabelContent = ({currentLanguage}) => {

const [data, setData] = useState([]); // 使用useState来管理data的状态

  // 异步获取数据
  useEffect(() => {
    async function fetchDataAsync() {
      try {
        const result = await getTags();
        console.log(result);
        setData(result); // 更新data的值
      } catch (error) {
        console.error(error); // 处理错误
      }
    }

    fetchDataAsync();
  }, []);

  const label_txt = getText('label',currentLanguage);
  const save_txt = getText('save',currentLanguage);
  const delete_txt = getText('delete',currentLanguage);
  const cancel_txt = getText('cancel',currentLanguage);
  const edit_txt = getText('edit',currentLanguage);
  const operation_txt = getText('operation',currentLanguage);
  const add_txt = getText('add',currentLanguage);
  const enter_txt = getText('enter',currentLanguage);
  const name_txt = getText('name',currentLanguage);
  const enter_label_id = enter_txt+" "+label_txt+" id";
  const enter_label_name = enter_txt+" "+label_txt+" "+name_txt;

  const [editingId, setEditingId] = useState(null);
  const [modalIsOpen, setModalIsOpen] = useState(false);
  const [newName, setNewName] = useState('');
  const [newLabelId, setNewLabelId] = useState('');
  const [newLabelName, setNewLabelName] = useState('');

  const handleEdit = (id) => {
    setEditingId(id);
    setModalIsOpen(true);
    const selectedItem = data.find(item => item.id === id);
    setNewName(selectedItem.name);
  };

  const handleSave = () => {
    const updatedData = data.map(item => {
      if (item.id === editingId) {
        return { ...item, name: newName };
      }
      return item;
    });
    editTag(editingId,newName);
    setData(updatedData);
    setEditingId(null);
    setModalIsOpen(false);
  };

  const handleDelete = (id) => {
    const updatedData = data.filter(item => item.id !== id);
    deleteTag(id);
    setData(updatedData);
    setEditingId(null);
    setModalIsOpen(false);
  };

  const closeModal = () => {
    setModalIsOpen(false);
    setEditingId(null);
    setNewName('');
  };

  const handleAddLabel = async () => {
    try {
      if(newLabelName.trim() === ''){
        alert('标签名称不能为空');
        return;
      }
      if(newLabelId.trim() === ''){
        alert('标签ID不能为空');
        return;
      }
      // 调用适当的API将新标签添加到数据源中
      await addTag(newLabelId,newLabelName.trim());
      // 获取更新后的标签列表数据
      const updatedData = await getTags();
      // 更新组件状态以显示新的标签列表
      setData(updatedData);
      // 重置新标签名称的状态
      setNewLabelId('');
      setNewLabelName('');
    } catch (error) {
      console.error(error);
    }
  };

  return (
    <div className="label-component">
      <h2>{label_txt}</h2>
      <table>
        <thead>
          <tr>
            <th>ID</th>
            <th>{label_txt}</th>
            <th>{operation_txt}</th>
          </tr>
        </thead>
        <tbody>
          {data.map(item => (
            <tr key={item.id}>
              <td>{item.id}</td>
              <td>
                  {item.name}
              </td>
              <td>
                <button className="edit-button" onClick={() => handleEdit(item.id)}>{edit_txt}</button>
                <button className="delete-button" onClick={() => handleDelete(item.id)}>{delete_txt}</button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>
      
      <div className='add-container'>
        <div className='input-container'>
        <input
          type="text"
          value={newLabelId}
          onChange={e => setNewLabelId(e.target.value)}
          placeholder={enter_label_id}
          className='input-field'
        />
        </div>
        <div className='input-container'>
        <input
          type="text"
          value={newLabelName}
          onChange={e => setNewLabelName(e.target.value)}
          placeholder={enter_label_name}
          className='input-field'
        />
        </div>
      
        <button onClick={handleAddLabel} className="add-button">{add_txt} {label_txt}</button>
      </div>
      <Modal
        isOpen={modalIsOpen}
        onRequestClose={closeModal}
        contentLabel="Edit Modal"
        className="modal"
      >
        <div className="modal-container">
        <h2 className="modal-title">{edit_txt} {label_txt}</h2>
        <div className="input-container">
            <label className="input-label">{label_txt}：</label>
            <input
                type="text"
                value={newName}
                onChange={(e) => setNewName(e.target.value)}
            />
          </div>
          <div className="button-container">
            <button className="modal-button" onClick={handleSave}>{save_txt}</button>
            <button className="modal-button" onClick={closeModal}>{cancel_txt}</button>
          </div>
        </div>
      </Modal>
    </div>
  );
};

function mapStateToProps(state) {
    return {
      currentLanguage: state.language.language,
    };
  }
  
  export default connect(mapStateToProps)(LabelContent);