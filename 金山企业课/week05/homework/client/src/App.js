import React from 'react';
import Header from './pages/Header/Header';
import Sidebar from './pages/Sidebar/Sidebar';
import MainContent from './pages/MainContent/MainContent';
import './App.css';
import store from './redux/store';
import { Provider } from 'react-redux';
import { useState } from 'react';
import LabelContent from './pages/LabelContent/LabelContent';

const App = () => {
  // 假设这里有一些示例的标签数据
  const tags = ['数据管理', '标签管理'];

  const [selectedTag, setSelectedTag] = useState(tags[0]); // 默认选中第一个标签

  const handleTagSelect = (tag) => {
    setSelectedTag(tag);
  };

  return (
    <Provider store={store}>
      <div className="App">
        <Header />
        <div className="content">
          <Sidebar tags={tags} onSelectTag={handleTagSelect} selectedTag={selectedTag} />
          {selectedTag === '数据管理' && <MainContent />}
          {selectedTag === '标签管理' && <LabelContent />}
        </div>
      </div>
    </Provider>
    
  );
}

export default App;