import { createStore, combineReducers } from 'redux';
import { languageReducer } from './language';

// 整合reducer
const rootReducer = combineReducers({
  language: languageReducer
});

// 创建store
const store = createStore(rootReducer);

export default store;