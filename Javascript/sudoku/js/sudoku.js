/**
* author:zh
* email:15527597628@163.com
* date:2020年5月17日
*/

var timeStart;
var countTime = false;
var count = 0;
var timerId = -1;
function endTimer() {
  countTime = false;
  clearTimeout(timerId);
  //console.log(timerId);
}
function startTimer() {
  timeStart = new Date();
  countTime = true;
  count = 0;
  timeObj.innerHTML =  "00 : 00 : 00";
  timerId = setTimeout(timer, 1000);
  //console.log(timerId);
}
function timer() {
  count++;
  var h = pad(parseInt(count / 3600));
  var m = pad(parseInt(count / 60));
  var s = pad(parseInt(count % 60));
  timeObj.innerHTML = h + " : " + m + " : " + s;
  if (countTime) {
    timerId = setTimeout(timer, 1000);
  }
}
function pad(i) {
  if (i < 10) {
    return "0" + i;
  }
  return i;
}

function SUDO(){
	this.initSudokuArray=[9,7,8,3,1,2,6,4,5,
		3,1,2,6,4,5,9,7,8,
		6,4,5,9,7,8,3,1,2,
		7,8,9,1,2,3,4,5,6,
		1,2,3,4,5,6,7,8,9,
		4,5,6,7,8,9,1,2,3,
		8,9,7,2,3,1,5,6,4,
		2,3,1,5,6,4,8,9,7,
		5,6,4,8,9,7,2,3,1];
	this.rotateArray=[];
	this.blankNumber = 30;
	this.clicked=[0,0,0,0,0,0,0,0,0,0];
	this.choosed=0;
	this.curSudokuArray=[];
}
SUDO.prototype={
	constructor:SUDO,
	init:function(){
		this.createDoms();
		//var beTime = new Date().getTime();
		this.createSudokuArray();
		this.blankNum = this.setLevel()||this.blankNum;
		//$(".sdspan[contenteditable=true]").prop('contenteditable',false);// 设置属性和值
		this.drawCells();
		this.createBlank(this.blankNumber);

	},
	// 生成九宫格 显示
	createDoms:function(){
		var init_html = '<ul class="sd wholeblock">',html='';
		//String.prototype.times = function(n) { return (new Array(n+1)).join(this);}; // 字符串乘法
		for(var i=0;i<9;i++){
			var tmp='';
			for(var j=0;j<9;j++){
				tmp = tmp+('<span id="span')+i+j+'" class="sdspan"></span>';
			}
			html = html + '<li id="sdli'+i+'" class="sdli" >'+tmp+'</li>';
		}
		html = init_html+html+'</ul>';
		//$("div").prepend(html); // 来自jquery库
		$("h1").append(html); //h1后面加入
		//$(".sdli:eq(0) .sdspan").addClass('outbt');
		$(".sdli:eq(8) .sdspan").addClass('outbb');
		for(var k=0;k<9;k++){ 
			$(".sdli:eq("+k+") .sdspan").eq(2).addClass('br');
			$(".sdli:eq("+k+") .sdspan").eq(5).addClass('br');
			$(".sdli:eq("+k+") .sdspan").eq(3).addClass('bl');
			$(".sdli:eq("+k+") .sdspan").eq(6).addClass('bl');
			$(".sdli:eq("+k+") .sdspan").eq(0).addClass('outbl');
			$(".sdli:eq("+k+") .sdspan").eq(8).addClass('outbr');
			$(".sdli:eq(0) .sdspan").eq(k).addClass('outbt');
		}
		$(".sdli:eq(2) .sdspan,.sdli:eq(5) .sdspan").addClass('bb'); // 直接在3,6行底部加粗 blue
		$(".sdli:eq(3) .sdspan,.sdli:eq(6) .sdspan").addClass('bt'); // 4,7行顶部加粗 blue
		
		// 

		for(var k=0;k<3;k++){
			for(var j=3;j<6;j++){
				$(".sdli:eq("+k+") .sdspan").eq(j).addClass('bg');	
			}
		}	
		for(var k=3;k<6;k++){
			for(var j=0;j<3;j++){
				$(".sdli:eq("+k+") .sdspan").eq(j).addClass('bg');	
				$(".sdli:eq("+k+") .sdspan").eq(j+6).addClass('bg');
			}
		}
		for(var k=6;k<9;k++){
			for(var j=3;j<6;j++){
				$(".sdli:eq("+k+") .sdspan").eq(j).addClass('bg');	
			}
		}		
		html = '<div id="setbg"></div>'
		$(".bg").prepend(html); 
	},
	
	// 生成数独(答案数组)
	createSudokuArray:function(){
		var Iarray = [1,2,3,4,5,6,7,8,9];
		for(var i=0;i<9;i++){
			var xx = Math.floor(Math.random()*(9-i));// 生成0-8的随机数
			this.rotateArray.push(Iarray[xx]); 
			Iarray.splice(xx,1);// 删除xx索引元素
		}
		console.log(this.initSudokuArray);
		for (var k = 0; k < 9; k++){
			var swapnum1 = this.initSudokuArray[k];
			var swapnum2 = this.rotateArray[k];
			for (var i = 0; i < 9; i++)
			{
				for (var j = 0; j < 9; j++) {
					if (this.initSudokuArray[i * 9 + j] == swapnum1) {
						this.initSudokuArray[i * 9 + j] = swapnum2;
					}
					else if (this.initSudokuArray[i * 9 + j] == swapnum2) {
						this.initSudokuArray[i * 9 + j] = swapnum1;
					}
				}
			}
		}
		console.log(this.initSudokuArray);
	},
	
	// 数独数组中删除一些元素，让玩家回答
	createBlank:function(num){
		// 随机生成num个数的空白格子坐标
		var blankLoaction = [];
		var numArray = [1,2,3,4,5,6,7,8,9];
		for(var a =0;a<num;a++){
			do{
				var item = parseInt(numArray[Math.floor(Math.random()*9)] +''+ numArray[Math.floor(Math.random()*9)]);
			}while($.inArray(item, blankLoaction)>-1); // 查找数组中是否存在item，若存在，则重新随机生成一个坐标
			blankLoaction.push(item);
		}
		//this.blankLoaction = blankLoaction;
		// 去除格子值，由用户填写答题，把格子变成可编辑，并添加事件
		var x,y,dom;
		//console.log(blankLoaction);
		for(var i =0;i<num;i++){
			x = parseInt(blankLoaction[i]/10); // 十位是第几行，个位是第几列
			y = blankLoaction[i]%10;	
			dom = $(".sdli").eq(x-1).find(".sdspan").eq(y-1);// 格子点
			dom.attr('contenteditable', true).html('').addClass('blankCell');// attr()设置属性为编辑状态，设置html为空，并增加class
			//onclick="sd.put()"
			dom.attr('onclick',"sd.put()");
			this.curSudokuArray[9*(x-1)+y-1]=0;
		}
		$(".sdspan[contenteditable=true]").keyup(function(event) {
			var val = $(this).html();			
			var reStr = /^[1-9]{1}$/; // 正则表达式，只取一位数
			if(!reStr.test(val)){
				$(this).html('');
			};
		});
		this.init_array = this.curSudokuArray;
	},
	
	setLevel:function(){
		//用户输入难度。
		var num = document.getElementById('setNum').value;  // 值范围5-50
		if(!isNaN(num)){
			num = parseInt(num);
			num = num<5?5:num;
			num = num>50?50:num;
		}else{
			num=30;
		}
		return num;
	},
	
	//将生成的数组填写到九宫格
	drawCells:function(){
		for(var j =0;j<9;j++){
			for(var i =0;i<9;i++){					
				$(".sdli").eq(j).find(".sdspan").eq(i).html(this.initSudokuArray[9*j+i]);
			}
		}
		this.curSudokuArray = this.initSudokuArray;
	},
	
	choose:function(){
		//	this.clicked=[0,0,0,0,0,0,0,0,0,0];
		//document.body.style.cursor="url('img/1.png'),hand"; // 自定义鼠标样式
		$(".bg_red").removeClass('bg_red');
		var obj=document.elementFromPoint(event.clientX,event.clientY); // 获取鼠标点击时的对象
		var clickId = obj.id;
		var val = obj.innerText;
		//console.log("点击了"+val);
		if(val=='X'){
			$(".show_choose").removeClass('show_choose');
			document.body.style.cursor="auto";
			this.clicked=[0,0,0,0,0,0,0,0,0,0];
			for(var i=1;i<=9;i++){
				document.getElementById('C'+i).style.cssText = "border:1px solid green";
				this.choosed = 10; // 选中
				$(".bg_red").removeClass('bg_red');
			}
		}else{
			val = val-1;
			$(".show_choose").removeClass('show_choose');
			this.showChoose(val+1);
			if(this.clicked[val]==0){
				this.clicked=[0,0,0,0,0,0,0,0,0,0];
				for(var i=1;i<=9;i++){
					document.getElementById('C'+i).style.cssText = "border:1px solid green";
				}
				this.clicked[val] = 1;
				this.choosed = val+1;
				obj.style.cssText = "border: 1px solid red";// 设置属性和值
				document.body.style.cursor="url('img/"+(val+1)+".png'),hand";
				
			}else{ // 点击过
				this.clicked[val] = 0;
				obj.style.cssText = "border: 1px solid green";// 设置属性和值
				document.body.style.cursor="auto";
			}	
		}
	},
	showError:function(x,y){
		$(".bg_red").removeClass('bg_red');
		var dom;
		var isError = false;
		// 检查rows
		for(var i=0;i<9;i++){
			if(this.choosed==this.curSudokuArray[9*x+i]){
				dom = $(".sdli").eq(x).find(".sdspan").eq(i);
				dom.addClass('bg_red');
				isError=true;
			}
		}
		// 检查cols
		for(var i=0;i<9;i++){
			if(this.choosed==this.curSudokuArray[9*i+y]){
				dom = $(".sdli").eq(i).find(".sdspan").eq(y);
				dom.addClass('bg_red');
				isError=true;
			}
		}
		// 检查宫
	  	var startRow = Math.floor(x / 3) * 3;
		var startCol = Math.floor(y / 3) * 3;
		for (var i = 0; i < 3; i++) {
		    for (var j = 0; j < 3; j++) {
		    	if (this.curSudokuArray[(startRow + i)*9+startCol + j] === this.choosed) {
		        	dom = $(".sdli").eq(startRow + i).find(".sdspan").eq(startCol + j);
					dom.addClass('bg_red');
					isError=true;
		      	}
		    }
		}
		return isError;
	},
	// 计算被选择数字位置，显示其数字方框或者背景，统计答题的数组
	put:function(){
		var instanceId=document.elementFromPoint(event.clientX,event.clientY).id; // 获取鼠标点击时的对象的id span01-99; 
		//id[4]表示行索引，id[5]表示列索引
		var x,y,err=false;
		x = parseInt(instanceId[4]), y=parseInt(instanceId[5]);
		if(this.choosed<10&&this.choosed>0)
			err = this.showError(x,y);
		if(!err&&this.choosed!=0){ // 填充没有违反规则的数字
			$(".sdli").eq(x).find(".sdspan").eq(y).html(this.choosed);
			this.curSudokuArray[9*x+y]=this.choosed;
			
			// 判断是否完成游戏console.log($("span:empty").length);
			var isBlankNum = $("span:empty").length;
			if(isBlankNum==0){
				alert('you win!');
				
			}
				
		}
	},
	
	showChoose:function(val){
		var idname;
		for(var i=0;i<9;i++){
			for(var j=0;j<9;j++){
				if(this.curSudokuArray[9*i+j]==val){
					$(".sdli:eq("+i+") .sdspan").eq(j).addClass('show_choose');
				}
			}
		}
	},
	 inputDiff:function(){
		if(value>50){
			value=50;
			if(value.length>2){
				value=value.slice(0,2);
				if(value<1){
					value=1;
				}
	 		}
		}
	},
	refresh:function(){
	$(".show_choose").removeClass('show_choose');
	this.initSudokuArray=[9,7,8,3,1,2,6,4,5,
		3,1,2,6,4,5,9,7,8,
		6,4,5,9,7,8,3,1,2,
		7,8,9,1,2,3,4,5,6,
		1,2,3,4,5,6,7,8,9,
		4,5,6,7,8,9,1,2,3,
		8,9,7,2,3,1,5,6,4,
		2,3,1,5,6,4,8,9,7,
		5,6,4,8,9,7,2,3,1];
	this.rotateArray=[];
	this.blankNumber = 30;
	this.clicked=[0,0,0,0,0,0,0,0,0,0];
	this.choosed=0;
	this.curSudokuArray=[];
	$(".sdspan").removeClass('bg_red blankCell');
	this.createSudokuArray();
	this.blankNumber = this.setLevel()||this.blankNum;
	console.log(this.blankNumber)
	this.drawCells();
	$(".sdspan[contenteditable=true]").attr('contenteditable', false);
	this.createBlank(this.blankNumber);
	endTimer();
	startTimer();
	},
	
}
//	this.clicked=[0,0,0,0,0,0,0,0,0,0];
//	this.choosed=0;
//	this.curSudokuArray=[];
