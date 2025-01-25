import React from 'react';
import './MainContent.css';
import SearchBox from '../SearchBox/SearchBox';
import DataDisplay from '../DataDisplay/DataDisplay';
import { useEffect,useState } from 'react';
import { fetchData } from '../../axios/Data';

const MainContent = ({currentLanguage}) => {
  const [data, setData] = useState([]); // 使用useState来管理data的状态

  // 异步获取数据
  useEffect(() => {
    async function fetchDataAsync() {
      try {
        const result = await fetchData();
        setData(result); // 更新data的值
      } catch (error) {
        console.error(error); // 处理错误
      }
    }

    fetchDataAsync();
  }, []); // 只在组件加载时调用一次
  
  const searchData = async (name, tag, selectedTime) => {
    try {
      const query = { name, tag, selectedTime };
      console.log(query);
      const result = await fetchData(query);
      setData(result);
    } catch (error) {
      console.error(error); // 处理错误
    }
  };

  return (
    <div className="main-content-container">
      <SearchBox searchData={searchData}/>
      <DataDisplay data={data}/>
    </div>
  );
}

export default MainContent;