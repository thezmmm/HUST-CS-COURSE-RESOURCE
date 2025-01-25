import React from 'react';
import SettingsDropdown from './SettingsDropdown/SettingsDropdown';
import './Header.css';
import { getText } from '../../redux/i18n';
import { connect } from 'react-redux';

const Header = ({ currentLanguage }) => {
  const handleLanguageChange = (selectedLanguage) => {
    // 处理语言切换逻辑
    console.log('切换语言:', selectedLanguage);
  };

  const title = getText('title', currentLanguage);
  return (
    <header className="header-container">
      <div className="header-left">
        <span>{title}</span>
      </div>
      <div className="header-right">
        <SettingsDropdown onLanguageChange={handleLanguageChange} />
      </div>
    </header>
  );
};

function mapStateToProps(state) {
  return {
    currentLanguage: state.language.language,
  };
}

export default connect(mapStateToProps)(Header);