// 定义action类型
const SET_LANGUAGE = 'SET_LANGUAGE';

// 定义action创建函数
export function setLanguage(language) {
  return {
    type: SET_LANGUAGE,
    payload: language,
  };
}

// 定义初始状态
const initialState = {
  language: 'zh', // 默认语言为中文
};

// 定义reducer
export function languageReducer(state = initialState, action) {
  switch (action.type) {
    case SET_LANGUAGE:
      return {
        language: action.payload,
      };
    default:
      return state;
  }
}