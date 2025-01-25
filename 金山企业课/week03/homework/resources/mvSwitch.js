var verisonNum = 0;
var areaNum = 0;
var fileName = 'new.json';


var tagLists = document.querySelectorAll('.tag_list');
// tag switch click event
tagLists.forEach(function(tagList) {
    tagList.addEventListener('click', function(event) {
        if (event.target.classList.contains('tag_item')) {
            var tagItems = this.querySelectorAll('.tag_item');

            tagItems.forEach(function(tagItem) {
                tagItem.classList.remove('tag_item_select');
            });

            event.target.classList.add('tag_item_select');

            var tagItemText = event.target.textContent.trim();
            var areaKeys = Object.keys(area);
            var verisonKeys = Object.keys(verison);
            
            areaKeys.forEach(function(key) {
                if (area[key] === tagItemText) {
                    areaNum = parseInt(key);
                }
            });
            
            verisonKeys.forEach(function(key) {
                if (verison[key] === tagItemText) {
                    verisonNum = parseInt(key);
                }
            });
            
            console.log("areaNum:", areaNum);
            console.log("verisonNum:", verisonNum);
        }
        mvItemInsert(fileName,areaNum,verisonNum);
    });

});

var partDetailTagItems = document.querySelectorAll('.part_detail_tag span');
partDetailTagItems.forEach(function(tagItem) {
    tagItem.addEventListener('click', function() {
        // 移除所有 tag_item_select 的类名
        partDetailTagItems.forEach(function(item) {
            item.classList.remove('part_detail_tag_item_select');
        });

        // 将当前点击的 span 添加 tag_item_select 类名
        this.classList.add('part_detail_tag_item_select');
        
        // 修改fileName
        console.log(this.textContent);
        if(this.textContent === '最新'){
            fileName = 'new.json';
        }else if(this.textContent === '最热'){
            fileName = 'hot.json';
        }

        // 调用mvItemInsert
        mvItemInsert(fileName,areaNum,verisonNum);
    });
});