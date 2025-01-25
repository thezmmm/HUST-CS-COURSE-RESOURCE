// i18n.js
import en from '../locales/en.json';
import zh from '../locales/zh.json';

const locales = {
  en,
  zh,
};

export const getText = (key, language) => {
  const locale = locales[language];
  if (locale && locale[key]) {
    return locale[key];
  }
  return '';
};