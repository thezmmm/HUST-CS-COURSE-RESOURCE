import React, { useEffect,useState } from 'react';
import './DataDisplay.css';
import { getText } from '../../redux/i18n';
import { connect } from 'react-redux';
import { editData,deleteData } from '../../axios/Data';
import Modal from 'react-modal';
import { getTags } from '../../axios/Label';



// 表头组件
const TableHeader = ({no,name,description,addTime,label,operation}) => {

  return (
    <div className="header">
      <span>{no}</span>
      <span>{name}</span>
      <span>{description}</span>
      <span>{addTime}</span>
      <span>{label}</span>
      <span>{operation}</span>
    </div>
  );
};

// 数据行组件
const DataRow = ({ item,edit_txt,delete_txt,save_txt,cancel_txt,name,description,addTime,label,tags }) => {
  const [isModalOpen, setIsModalOpen] = useState(false); // 模态框打开状态
  const [editedData, setEditedData] = useState({
    id: item.id,
    name: item.name,
    description: item.description,
    time: item.time,
    tagId: item.tagId
  });

  // 更新编辑数据字段
  const handleFieldChange = (field, value) => {
    setEditedData((prevData) => ({
      ...prevData,
      [field]: value
    }));
  };

  // 保存编辑后的数据
  const saveEditedData = async () => {
    try {
      await editData(editedData.id,editedData);
      window.location.reload(); // 刷新页面
      setIsModalOpen(false); // 保存成功后关闭模态框
      // console.log('Data edited successfully');
    } catch (error) {
      console.error('Failed to edit data:', error.message);
    }
  };

  // 编辑按钮点击事件处理函数
  const handleEdit = () => {
    setIsModalOpen(true);
  };

  // 取消编辑
  const cancelEdit = () => {
    setIsModalOpen(false);
  };

  // 删除按钮点击事件处理函数
  const handleDelete = async () => {
    try {
      await deleteData(item.id);
      window.location.reload(); // 刷新页面
      // console.log('Data deleted successfully');
    } catch (error) {
      console.error('Failed to delete data:', error.message);
    }
  };

  // 将tagId转换成tagName
  function convertTagIdsToNames(tagIdString, tagsArray) {
    const tagNames = [];
    const tagIds = tagIdString.split(/[,\s]+/);
  
    for (const tagId of tagIds) {
      const tag = tagsArray.find(tag => tag.id === tagId);
  
      if (tag) {
        tagNames.push(tag.name);
      } else {
        tagNames.push(tagId);
      }
    }
  
    return tagNames.join("  ");
  }

  return (
    <div className="data-row" key={item.id}>
      <span>{item.id}</span>
      <span>{item.name}</span>
      <span>{item.description}</span>
      <span>{item.time}</span>
      <span>{convertTagIdsToNames(item.tagId,tags)}</span>
      <span>
        <button onClick={handleEdit} className='edit-button'>{edit_txt}</button>
        <button onClick={handleDelete} className='delete-button'>{delete_txt}</button>
      </span>
      <Modal
        isOpen={isModalOpen}
        onRequestClose={cancelEdit}
        contentLabel="Edit Data Modal"
      >
        <div className='modal-container'>
          <h2 className='modal-title'>{edit_txt} data</h2>
          <div className="input-container">
            <label className="input-label">{name}：</label>
            <input
              type="text"
              value={editedData.name}
              onChange={(e) => handleFieldChange('name', e.target.value)}
            />
          </div>
          <div className="input-container">
            <label className="input-label">{description}：</label>
            <input
              type="text"
              value={editedData.description}
              onChange={(e) => handleFieldChange('description', e.target.value)}
            />
          </div>
          <div className="input-container">
            <label className="input-label">{addTime}：</label>
            <input
            type="text"
            value={editedData.time}
            onChange={(e) => handleFieldChange('time', e.target.value)}
            />
          </div>
          <div className="input-container">
            <label className="input-label">{label}：</label>
            <input
            type="text"
            value={editedData.tagId}
            onChange={(e) => handleFieldChange('tagId', e.target.value)}
            />
          </div>
          
          <div className="button-container">
            <button onClick={saveEditedData} className='modal-button'>{save_txt}</button>
            <button onClick={cancelEdit} className='modal-button'>{cancel_txt}</button>
          </div>
        </div>
        
      </Modal>
    </div>
  );
};

// 分页组件
const Pagination = ({ totalPages, currentPage, onPageChange, pageSizeOptions, onPageSizeChange,currentLanguage }) => {
  const [pageSize, setPageSize] = useState(pageSizeOptions[0]);

  // 切换页码
  const handlePageChange = (page) => {
    onPageChange(page);
  };

  // 切换每页显示数量
  const handlePageSizeChange = (event) => {
    const newPageSize = parseInt(event.target.value);
    setPageSize(newPageSize);
    onPageSizeChange(newPageSize);
  };

  let pageInfoText;
  let itemPageText;
  if (currentLanguage === "en") {
    pageInfoText = `Page ${currentPage} of ${totalPages}`;
    itemPageText = `items/Page`;
  } else if (currentLanguage === "zh") {
    pageInfoText = `第 ${currentPage} 页，共 ${totalPages} 页`;
    itemPageText = `条/页`;
  } else {
    pageInfoText = `Page ${currentPage} of ${totalPages}`;
    itemPageText = `items/Page`;
  }

  return (
    <div className="pagination">
      <button
        className="arrow-button"
        disabled={currentPage === 1}
        onClick={() => handlePageChange(currentPage - 1)}
      >
        &lt; 
      </button>

      <span className="page-info">
        {pageInfoText}
      </span>

      <button
        className="arrow-button"
        disabled={currentPage === totalPages}
        onClick={() => handlePageChange(currentPage + 1)}
      >
         &gt;
      </button>

      <select value={pageSize} onChange={handlePageSizeChange}>
        {pageSizeOptions.map((option) => (
          <option key={option} value={option}>
            {option} {itemPageText}
          </option>
        ))}
      </select>
    </div>
  );
};

// 主组件
const DataDisplay = ({data,currentLanguage}) => {

  const no = getText('no',currentLanguage);
  const name = getText('name',currentLanguage);
  const description = getText('description',currentLanguage);
  const addTime = getText('addTime',currentLanguage);
  const label = getText('label',currentLanguage);
  const operation = getText('operation',currentLanguage);
  const save_txt = getText('save',currentLanguage);
  const delete_txt = getText('delete',currentLanguage);
  const cancel_txt = getText('cancel',currentLanguage);
  const edit_txt = getText('edit',currentLanguage);

  // 分页相关状态
  const [currentPage, setCurrentPage] = useState(1);
  const [pageSize, setPageSize] = useState(10);
  const totalPages = Math.ceil(data.length / pageSize);
  const startIndex = (currentPage - 1) * pageSize;
  const endIndex = currentPage * pageSize;

  // 标签数据
  const [tags, setTags] = useState([]); // 使用useState来管理data的状态

  // 异步获取数据
  useEffect(() => {
    async function fetchDataAsync() {
      try {
        const result = await getTags();
        console.log(result);
        setTags(result);
      } catch (error) {
        console.error(error); // 处理错误
      }
    }

    fetchDataAsync();
  }, []);

  // 切换页码
  const handlePageChange = (page) => {
    setCurrentPage(page);
  };

  // 切换每页显示数量
  const handlePageSizeChange = (newPageSize) => {
    setPageSize(newPageSize);
    setCurrentPage(1); // 切换每页显示数量时，重置当前页码为第一页
  };

  // 更新分页相关状态
  useEffect(() => {
    const newPageSize = parseInt(5);
    setPageSize(newPageSize);
    handlePageSizeChange(newPageSize);
  }, [data]);

  return (
    <div>
      <TableHeader
        no={no}
        name={name}
        description={description}
        addTime={addTime}
        label={label}
        operation={operation}
      />

      <div className="data">
        {data.slice(startIndex, endIndex).map((item) => (
          <DataRow 
            key={item.id} item={item}
            edit_txt={edit_txt}
            delete_txt={delete_txt}
            save_txt={save_txt}
            cancel_txt={cancel_txt}
            name={name}
            description={description}
            addTime={addTime}
            label={label}
            tags={tags} />
        ))}
      </div>

      <Pagination
        totalPages={totalPages}
        currentPage={currentPage}
        onPageChange={handlePageChange}
        pageSizeOptions={[5, 10, 20]} // 可选的每页显示数量
        onPageSizeChange={handlePageSizeChange}
        currentLanguage = {currentLanguage}
      />
    </div>
  );
};
function mapStateToProps(state) {
  return {
    currentLanguage: state.language.language,
  };
}

export default connect(mapStateToProps)(DataDisplay);