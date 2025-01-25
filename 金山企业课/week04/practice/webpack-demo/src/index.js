import _ from "lodash";

function component() {
    const element = document.createElement('div');
  
    // loadsh 现在使用import引入

    element.innerHTML = _.join(['Hello', 'webpack'], ' ');
  
    return element;
  }
  
  document.body.appendChild(component());