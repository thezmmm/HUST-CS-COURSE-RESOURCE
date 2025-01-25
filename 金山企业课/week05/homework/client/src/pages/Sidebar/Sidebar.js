import React from 'react';
import './Sidebar.css';
import { getText } from '../../redux/i18n';
import { connect } from 'react-redux';

const Sidebar = ({ tags, onSelectTag, selectedTag, currentLanguage }) => {
  const dataTag = getText('data-tag', currentLanguage);
  const labelTag = getText('label-tag',currentLanguage);
  console.log(dataTag);

  return (
    <div className="sidebar-container">
      <ul className="tag-list">
        {tags.map((tag, index) => (
          <li
            key={index}
            className={`tag-item ${tag === selectedTag ? 'selected' : ''}`}
            onClick={() => onSelectTag(tag)}
          >
            {index === 0 ? dataTag : index === 1 ? labelTag : tag}
          </li>
        ))}
      </ul>
    </div>
  );
}

function mapStateToProps(state) {
  return {
    currentLanguage: state.language.language,
  };
}

export default connect(mapStateToProps)(Sidebar);
