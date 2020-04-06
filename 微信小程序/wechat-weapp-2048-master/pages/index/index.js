//index.js
//获取应用实例
const app = getApp()

Page({
  data: {
    current: 0
  },  
  onReady: function() {
    this.load();
  },
  load: function() {
    var n = 1;// 设置n模拟加载的情况，current代表加载中点的位置，一共四个点，从0开始，3结束后归零
    var timer = setInterval(()=>{
      if(n == 2) {// 模拟加载的情况，可自由设置1-10
        clearInterval(timer);
        wx.redirectTo({
          url: '../2048/2048'// 加载2048画面
        })
      }
      this.setData({
        current: this.data.current+1
      });
      if(this.data.current > 3) 
        this.setData({
          current: 0
        });
        n++;
    }, 400);// 执行前面内容的时间间隔
  }
})