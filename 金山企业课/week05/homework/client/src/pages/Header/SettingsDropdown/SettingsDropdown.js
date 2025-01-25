import React, { useState } from 'react';
import { connect } from 'react-redux';
import { setLanguage } from '../../../redux/language';
import { getText } from '../../../redux/i18n';

const SettingsDropdown = ({ currentLanguage, onLanguageChange }) => {
  const [showDropdown, setShowDropdown] = useState(false);

  const toggleLanguage = (selectedLanguage) => {
    onLanguageChange(selectedLanguage);
    setShowDropdown(false);
  };

  const toggleDropdown = () => {
    setShowDropdown(prevState => !prevState);
  };

  const setting = getText('setting', currentLanguage);

  return (
    <div className="dropdown">
      <button onClick={toggleDropdown} className='setting-button'>{setting}</button>
      {showDropdown && (
        <ul className="dropdown-menu">
          <li onClick={() => toggleLanguage('en')}>English</li>
          <li onClick={() => toggleLanguage('zh')}>中文</li>
        </ul>
      )}
    </div>
  );
};

function mapStateToProps(state) {
  return {
    currentLanguage: state.language.language,
  };
}

const mapDispatchToProps = {
  onLanguageChange: setLanguage,
};

export default connect(mapStateToProps, mapDispatchToProps)(SettingsDropdown);