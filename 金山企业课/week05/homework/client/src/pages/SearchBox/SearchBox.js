import React, { useState } from 'react';
import './SearchBox.css';
import { getText } from '../../redux/i18n';
import { connect } from 'react-redux';
import Modal from 'react-modal';
import { addData } from '../../axios/Data';


const SearchBox = ({ searchData,currentLanguage }) => {

  const boxName = getText('name', currentLanguage);
  const boxLabel = getText('label', currentLanguage);
  const boxTime = getText('addTime', currentLanguage);
  const boxSearch = getText('search', currentLanguage);
  const boxReset = getText('reset', currentLanguage);
  const boxAdd = getText('add', currentLanguage);
  const boxChooseAddTime = getText('chooseAddTime', currentLanguage);
  const boxCancel = getText('cancel', currentLanguage);
  const boxDescription = getText('description', currentLanguage);
  const boxAddData = getText('addData', currentLanguage);
  const inputName = getText('inputName',currentLanguage);
  const inputDescription = getText('inputDescription',currentLanguage);
  const inputLabel = getText('inputTag',currentLanguage);
  const today_txt = getText('today',currentLanguage);
  const yesterday_txt = getText('yesterday',currentLanguage);
  const this_week_txt = getText('thisWeek',currentLanguage);
  const this_month_txt = getText('thisMonth',currentLanguage);
  const inputLabel_txt = getText('inputLabel',currentLanguage);
  const inputSearchName_txt = getText('inputSearchName',currentLanguage);

  const [name, setName] = useState('');
  const [tag, setTag] = useState('');
  const [time, setTime] = useState('');
  const [isModalOpen, setIsModalOpen] = useState(false);
  const [dataName, setDataName] = useState('');
  const [dataDescription, setDataDescription] = useState('');
  // const [dataTime, setDataTime] = useState('');
  const [dataTagId, setDataTagId] = useState('');

  const handleNameChange = (event) => {
    setName(event.target.value);
  };

  const handleTagChange = (event) => {
    setTag(event.target.value);
  };

  const handleTimeChange = (event) => {
    setTime(event.target.value);
  };

  const handleSearch = () => {
    // 调用 searchData 函数进行搜索
    searchData(name, tag, time);
  };

  const handleReset = () => {
    setName('');
    setTag('');
    setTime('');
    searchData();
  };

  const handleAdd = () => {
    setIsModalOpen(true);
  };

  const handleModalClose = () => {
    setIsModalOpen(false);
  };

  const handleDataNameChange = (event) => {
    setDataName(event.target.value);
  };

  const handleDataDescriptionChange = (event) => {
    setDataDescription(event.target.value);
  };

  // const handleDataTimeChange = (event) => {
  //   setDataTime(event.target.value);
  // };

  const handleDataTagIdChange = (event) => {
    setDataTagId(event.target.value);
  };

  const handleAddData = async () => {

    const currentDate = new Date();
    const formattedCurrentDate = currentDate.toISOString().split('.')[0];

    const newData = {
      name: dataName.trim(),
      description: dataDescription,
      time: formattedCurrentDate,
      tagId: dataTagId,
    };

    if (!newData.name) {
      alert('名称不能为空');
      return;
    }

    // 执行添加操作，使用 newData 对象作为新数据
    console.log('执行添加操作', newData);
    try {
      await addData(newData);
      searchData();
    } catch (error) {
      // 处理添加数据失败的情况
      console.error(error);
    }
    
    setIsModalOpen(false);
  };


  return (
    <div className="search-box-container">
        <div className='input-container'>
        <label className="input-label">{boxName}：</label>
        <input
        type="text"
        placeholder={inputSearchName_txt}
        value={name}
        onChange={handleNameChange}
      />
    </div>
    <div className='input-container'>
      <label className="input-label">{boxLabel}：</label>
      <input
        type="text"
        placeholder={inputLabel_txt}
        value={tag}
        onChange={handleTagChange}
      />
    </div>
    <div className='input-container'>
        <label className="input-label">{boxTime}：</label>
        <select value={time} onChange={handleTimeChange}>
            <option value="">{boxChooseAddTime}</option>
            <option value="today">{today_txt}</option>
            <option value="yesterday">{yesterday_txt}</option>
            <option value="this_week">{this_week_txt}</option>
            <option value="this_month">{this_month_txt}</option>
        </select>
    </div>
      <button onClick={handleSearch}>{boxSearch}</button>
      <button onClick={handleReset}>{boxReset}</button>
      <button onClick={handleAdd}>{boxAdd}</button>
      
      <Modal isOpen={isModalOpen} onRequestClose={handleModalClose}>
        <div className='modal-container'>
          <h2 className='modal-title'>{boxAddData}</h2>
          <div className="input-container">
            <label className="input-label">{boxName}：</label>
            <input type="text" placeholder={inputName} value={dataName} onChange={handleDataNameChange} />
          </div>
          <div className="input-container">
            <label className="input-label">{boxDescription}：</label>
            <input
              type="text"
              placeholder={inputDescription}
              value={dataDescription}
              onChange={handleDataDescriptionChange}
            />
          </div>
          <div className="input-container">
            <label className="input-label">{boxLabel} ID：</label>
            <input type="text" placeholder={inputLabel} value={dataTagId} onChange={handleDataTagIdChange} />
          </div>
          <div className="button-container">
            <button className="modal-button" onClick={handleAddData}>{boxAdd}</button>
            <button className="modal-button" onClick={handleModalClose}>{boxCancel}</button>
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

export default connect(mapStateToProps)(SearchBox);