// initialize mv list
mvItemInsert('new.json',0,0);

function mvItemInsert(fileName,area,verison){
  fetch('resources/'+fileName)
  .then(response => response.json())
  .then(jsonData => {
    // 在这里处理读取到的JSON数据
    // 获取包含<ul class="mv_list">的父元素
    var parentElement = document.querySelector('.part_detail');
    // 插入前清空之前插入的ul节点
    parentElement.removeChild(parentElement.querySelector('ul'));
    // 创建<ul class="mv_list">元素
    var ulElement = document.createElement('ul');
    ulElement.className = 'mv_list';
    
    // 遍历JSON数据并创建<li>元素
    jsonData.forEach(function(item) {
        // 筛选条件
        if((area==0||area==item.area) && (verison===0||verison==item.verison)){
          // 创建<li>元素
          var liElement = document.createElement('li');
          liElement.className = 'mv_list__item mv_list_slide__item';
          liElement.style.width = '25%';
          liElement.style.paddingBottom = 'undefinedpx';
      
          // 创建<div class="mv_list__item_box">元素
          var divElement = document.createElement('div');
          divElement.className = 'mv_list__item_box';
      
          // 创建<a>元素
          var aElement = document.createElement('a');
          aElement.className = 'mv_list__cover mod_cover';
          aElement.title = item.title;
      
          // 创建<img>元素
          var imgElement = document.createElement('img');
          imgElement.className = 'mv_list__pic';
          imgElement.loading = 'lazy';
          imgElement.src = item.picurl;
          imgElement.alt = item.title;
          imgElement.setAttribute('data-qar-def', '//y.qq.com/mediastyle/global/img/mv_300.png?max_age=2592000');
      
          // 创建<i>元素
          var iElement1 = document.createElement('i');
          iElement1.className = 'mod_cover__mask';
          var iElement2 = document.createElement('i');
          iElement2.className = 'mod_cover__icon_play';
      
          // 添加<img>和<i>元素到<a>元素
          aElement.appendChild(imgElement);
          aElement.appendChild(iElement1);
          aElement.appendChild(iElement2);
      
          // 创建<h3>元素
          var h3Element = document.createElement('h3');
          h3Element.className = 'mv_list__title';
          var aElement2 = document.createElement('a');
          aElement2.innerText = item.title;
          h3Element.appendChild(aElement2);
      
          // 创建<p>元素
          var pElement = document.createElement('p');
          pElement.className = 'mv_list__singer';
          var aElement3 = document.createElement('a');
          aElement3.className = 'playlist__author';
          aElement3.title = item.singers[0].name;
          aElement3.href = '/n/ryqq/singer/' + item.singers[0].mid;
          aElement3.innerText = item.singers[0].name;
          pElement.appendChild(aElement3);
      
          // 创建<div class="mv_list__info">元素
          var divElement2 = document.createElement('div');
          divElement2.className = 'mv_list__info';
          var spanElement = document.createElement('span');
          spanElement.className = 'mv_list__listen';
          var iElement3 = document.createElement('i');
          iElement3.className = 'mv_list__listen_icon sprite';
          spanElement.appendChild(iElement3);
          spanElement.innerText = item.playcnt;
          var pubdate = new Date(item.pubdate * 1000).toLocaleDateString();
          var divElement3 = document.createElement('div');
          divElement3.innerText = pubdate;
          divElement2.appendChild(spanElement);
          divElement2.appendChild(divElement3);
      
          // 添加<a>、<h3>、<p>和<div class="mv_list__info">元素到<div class="mv_list__item_box">元素
          divElement.appendChild(aElement);
          divElement.appendChild(h3Element);
          divElement.appendChild(pElement);
          divElement.appendChild(divElement2);
      
          // 添加<div class="mv_list__item_box">元素到<li>元素
          liElement.appendChild(divElement);
      
          // 添加<li>元素到<ul class="mv_list">元素
          ulElement.appendChild(liElement); 
        }
    });
    
    // 将<ul class="mv_list">元素添加到<div class="part_detail">中
    parentElement.appendChild(ulElement);
    })
  .catch(error => {
    // 处理错误
    console.error('发生错误:', error);
  });
  
}