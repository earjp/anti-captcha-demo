# -*- coding: gb2312 -*-
#! python
#author:lijia1991@gmail.com

import wx, os
from wx.lib.wordwrap import wordwrap
from wx.lib import imagebrowser
from ctypes import *


class MyMiniFrame(wx.MiniFrame):
    def __init__(
        self, parent, title, pos=wx.DefaultPosition, size=wx.DefaultSize,
        style=wx.DEFAULT_FRAME_STYLE,bm = "tmp.png"
        ):
        wx.MiniFrame.__init__(self, parent, -1, title, pos, size, style)

        image = wx.Image(bm, wx.BITMAP_TYPE_ANY)
        btp = image.ConvertToBitmap()
        wx.StaticBitmap(self,bitmap = btp)
        
class mainFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, title=u"验证码识别DEMO")
        self.CenterOnScreen()
        self.CreateStatusBar()
        self.SetStatusText("E-mail:lijia1991@gmail.com")
        mainFrame.createMenuBar(self)
        
        #Set icon
        icon = wx.EmptyIcon()
        iconpath = os.getcwd()
        icon.CopyFromBitmap(wx.Bitmap(os.path.join(iconpath,'icon.jpg'), wx.BITMAP_TYPE_ANY))
        self.SetIcon(icon)

        self.imageaddr = "004.png"
        self.outaddr = "tmp.png"
    
        self.pnl = wx.Panel(self)
        self.temp = wx.Image(self.imageaddr,wx.BITMAP_TYPE_ANY).ConvertToBitmap()
        self.bmp = wx.StaticBitmap(self.pnl,bitmap = self.temp)
        self.sbButton = wx.Button(self.pnl, -1, u"识别")
        self.Bind(wx.EVT_BUTTON, self.recog, self.sbButton)
        self.preButton = wx.Button(self.pnl, -1, u"预处理")
        self.Bind(wx.EVT_BUTTON, self.preprocess, self.preButton)
        self.txt = wx.TextCtrl(self.pnl)

        hbox = wx.BoxSizer()
        hbox.Add(self.preButton, proportion = 0, flag = wx.RIGHT, border = 5)
        hbox.Add(self.sbButton, proportion = 0, flag = wx.RIGHT, border = 5)
        hbox.Add(self.txt, proportion = 1)

        vbox = wx.BoxSizer(wx.VERTICAL)
        vbox.Add(hbox, proportion = 0, flag = wx.EXPAND | wx.ALL, border = 5)
        vbox.Add(self.bmp, proportion = 1,
                 flag = wx.EXPAND | wx.LEFT | wx.BOTTOM | wx.RIGHT, border = 5)
        
        self.pnl.SetSizer(vbox)
        
        #临时
        #aboutButton = wx.Button(self, -1, "Show a wx.AboutBox", (50,50))
        #self.Bind(wx.EVT_BUTTON, self.showAboutBox, aboutButton)
        #imgButton = wx.Button(self, -1, "Show a imagebrowser", (50,100))
        #self.Bind(wx.EVT_BUTTON, self.imgBrowser, imgButton)

    def recog(self, evt):
        dll = CDLL("antiCaptDll.dll")
        pout = c_char_p()
        #pans = c_char_p()
        pout.value = self.outaddr

        func = getattr(dll, "?tyKnow@@YAPADPAD@Z")
        pchar = func(pout)
        pans = c_char_p(pchar)
        
        self.txt.SetValue(pans.value)

    def preprocess(self, evt):
        #dir1 = os.getcwd()
        #dlldir = os.path.join(dir1, 'antiCaptDll.dll')
        dll = CDLL("antiCaptDll.dll")
        inaddr = self.imageaddr
        pin = c_char_p()
        pout = c_char_p()
        pin.value = inaddr
        pout.value = self.outaddr
        if self.submenu.IsChecked(233):
            func = getattr(dll, "?tyPreprocess@@YAXPAD0@Z")
            func(pin, pout)
        elif self.submenu.IsChecked(232):
            func = getattr(dll, "?tyTinyPreprocess@@YAXPAD0@Z")
            func(pin, pout)
        else:
            func = getattr(dll, "?tyLinePreprocess@@YAXPAD0@Z")
            func(pin, pout)
        #dll.tyPreprocess(pin, pout)
        
        win = MyMiniFrame(self, u"预处理结果",
                        style=wx.DEFAULT_FRAME_STYLE | wx.TINY_CAPTION_HORIZ, bm = self.outaddr)
        win.SetSize((300, 200))
        win.CenterOnParent(wx.BOTH)
        win.Show(True)

    #打开文件后
    def processFile(self, f):
        image = wx.Image(f, wx.BITMAP_TYPE_ANY)
        self.clearBmp(self.temp)#清除原先的那个位图
        self.temp= image.ConvertToBitmap()
        self.bmp.SetBitmap(self.temp)
        self.pnl.Refresh()#刷新self.pancel

    #清除位图，这个是抄的wxpython官方的demo
    def clearBmp(self, bmp):
        dc = wx.MemoryDC()
        dc.SelectObject(bmp)
        dc.SetBackground(wx.Brush("white"))
        dc.Clear()

    #创建菜单栏
    def createMenuBar(self):
        #文件
        fileMenu = wx.Menu()
        openFile = fileMenu.Append(-1, u"打开...\tCtrl-O", u"打开一个验证码图片")
        #config = fileMenu.Append(-1, u"设置", u"配置预处理过程")
        self.submenu = wx.Menu()
        self.submenu.AppendRadioItem(232, "简化")
        self.submenu.AppendRadioItem(233, "标准")
        self.submenu.AppendRadioItem(234, "去线")
        fileMenu.AppendMenu(-1, "配置", self.submenu)
        self.submenu.Check(233, True)
        #config.Enable(False)
        fileMenu.AppendSeparator()
        closeProg = fileMenu.Append(-1, u"退出\tCtrl-Q", u"退出程序")
        
        #帮助
        helpMenu = wx.Menu()
        abt = helpMenu.Append(-1, u"关于", u"关于此程序")

        #事件处理
        self.Bind(wx.EVT_MENU, self.imgBrowser, openFile)
        #self.Bind(wx.EVT_MENU, self.configer, config)
        self.Bind(wx.EVT_MENU, self.exitProg, closeProg)
        self.Bind(wx.EVT_MENU, self.showAboutBox, abt)
        
        accTable = wx.AcceleratorTable([(wx.ACCEL_CTRL, ord('O'), openFile.GetId()),
                                        (wx.ACCEL_CTRL, ord('Q'), closeProg.GetId())])
        self.SetAcceleratorTable(accTable)
        
        menuBar = wx.MenuBar()
        menuBar.Append(fileMenu, u"文件(&F)")
        menuBar.Append(helpMenu, u"帮助(&H)")
        self.SetMenuBar(menuBar)
        
    #配置
    def configer(self, evt):
        wx.MessageBox("Confinger!")
        
    #打开图片
    def imgBrowser(self, evt):
        dir = os.getcwd()
        initial_dir = os.path.join(dir, 'bitmaps')
        dlg = imagebrowser.ImageDialog(self, initial_dir)
        dlg.Centre()
        if dlg.ShowModal() == wx.ID_OK:
            self.imageaddr = dlg.GetFile()
            self.processFile(self.imageaddr)
        dlg.Destroy()

    #关于
    def showAboutBox(self, evt):
        info = wx.AboutDialogInfo()
        info.Name = u"验证码识别DEMO"
        info.Version = "0.1beta"
        info.Copyright = "(C) 2013"
        info.Description = wordwrap(
            u"用于演示通用的验证码预处理和识别\n"
            u"界面使用python2.7+wxPython2.8写成；图像处理使用C++语言；"
            u"识别部分使用Tesseract OCR引擎。\n希望对你有所帮助。",
            350, wx.ClientDC(self))
        info.Developers = [u"李嘉（合肥工大）"]
        licenseText = u"使用GNU通用公共授权（版本2）协议授权。"
        info.License = wordwrap(licenseText, 500, wx.ClientDC(self))
        wx.AboutBox(info)

    #退出
    def exitProg(self, evt):
        self.Close()

if __name__ == '__main__':
    app = wx.PySimpleApp()
    mainFrame().Show()
    app.MainLoop()
