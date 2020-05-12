// Mainframe macro generated from application: root.exe
// By ROOT version 6.18/04 on 2020-05-11 18:09:54

#ifndef ROOT_TGDockableFrame
#include "TGDockableFrame.h"
#endif
#ifndef ROOT_TGMenu
#include "TGMenu.h"
#endif
#ifndef ROOT_TGMdiDecorFrame
#include "TGMdiDecorFrame.h"
#endif
#ifndef ROOT_TG3DLine
#include "TG3DLine.h"
#endif
#ifndef ROOT_TGMdiFrame
#include "TGMdiFrame.h"
#endif
#ifndef ROOT_TGMdiMainFrame
#include "TGMdiMainFrame.h"
#endif
#ifndef ROOT_TGMdiMenu
#include "TGMdiMenu.h"
#endif
#ifndef ROOT_TGListBox
#include "TGListBox.h"
#endif
#ifndef ROOT_TGNumberEntry
#include "TGNumberEntry.h"
#endif
#ifndef ROOT_TGScrollBar
#include "TGScrollBar.h"
#endif
#ifndef ROOT_TGComboBox
#include "TGComboBox.h"
#endif
#ifndef ROOT_TGuiBldHintsEditor
#include "TGuiBldHintsEditor.h"
#endif
#ifndef ROOT_TGuiBldNameFrame
#include "TGuiBldNameFrame.h"
#endif
#ifndef ROOT_TGFrame
#include "TGFrame.h"
#endif
#ifndef ROOT_TGFileDialog
#include "TGFileDialog.h"
#endif
#ifndef ROOT_TGShutter
#include "TGShutter.h"
#endif
#ifndef ROOT_TGButtonGroup
#include "TGButtonGroup.h"
#endif
#ifndef ROOT_TGCanvas
#include "TGCanvas.h"
#endif
#ifndef ROOT_TGFSContainer
#include "TGFSContainer.h"
#endif
#ifndef ROOT_TGuiBldEditor
#include "TGuiBldEditor.h"
#endif
#ifndef ROOT_TGColorSelect
#include "TGColorSelect.h"
#endif
#ifndef ROOT_TGButton
#include "TGButton.h"
#endif
#ifndef ROOT_TGFSComboBox
#include "TGFSComboBox.h"
#endif
#ifndef ROOT_TGLabel
#include "TGLabel.h"
#endif
#ifndef ROOT_TRootGuiBuilder
#include "TRootGuiBuilder.h"
#endif
#ifndef ROOT_TGTab
#include "TGTab.h"
#endif
#ifndef ROOT_TGListView
#include "TGListView.h"
#endif
#ifndef ROOT_TGSplitter
#include "TGSplitter.h"
#endif
#ifndef ROOT_TGStatusBar
#include "TGStatusBar.h"
#endif
#ifndef ROOT_TGListTree
#include "TGListTree.h"
#endif
#ifndef ROOT_TGuiBldGeometryFrame
#include "TGuiBldGeometryFrame.h"
#endif
#ifndef ROOT_TGToolTip
#include "TGToolTip.h"
#endif
#ifndef ROOT_TGToolBar
#include "TGToolBar.h"
#endif
#ifndef ROOT_TGuiBldDragManager
#include "TGuiBldDragManager.h"
#endif

#include "Riostream.h"

//-----------------------------------------------------------------------------
class TestTabbed {
  // RQ_OBJECT("TestTabbed")
public: 
  TGMainFrame*        fMainFrame;
  TGTab *fTab ;

  TString             fStage;
  TString             fIStage;

  TGCompositeFrame*   fFrame[100];
  TGTabElement*       fActiveTab;

  Pixel_t             fYellow;
  Pixel_t             fTabColor;
  
  TestTabbed(const TGWindow *p, UInt_t w, UInt_t h);
  virtual ~TestTabbed();

  void     DoTab(Int_t id);
  void     BuildGui(const TGWindow *Parent, UInt_t Width, UInt_t Height);

}; 

//-----------------------------------------------------------------------------
TestTabbed::TestTabbed(const TGWindow *p, UInt_t w, UInt_t h) {
  BuildGui(p,w,h);
}

//-----------------------------------------------------------------------------
TestTabbed::~TestTabbed() {
   fMainFrame->Cleanup();
}


//-----------------------------------------------------------------------------
void TestTabbed::DoTab(Int_t id) {
  printf("Tab item %d activated\n", id);

  fStage = "undefined";

  if (id == 0) {
    fIStage = "gen:50_200000";
    fStage  = "s1:sim";
  }
  else if (id == 1) {
    fStage  = "s2:sim";
    fIStage = "s1:mubeam";
  }
  else if (id == 3) {
    fStage  = "s3:sim";
    fIStage = "s2:mubeam";
  }
  else if (id == 4) {
    fStage  = "s3:stn";
    fIStage = "s3:tgtstops";
  }
  else if (id == 5) {
    fStage  = "ts1:sim";
    fIStage = "pbar:vd91";
  }
  else if (id == 6) {
    fStage  = "ts2:sim";
    fIStage = "ts1:mubeam";
  }
  else if (id == 7) {
    fStage  = "ts3:sim";
    fIStage = "ts2:mubeam";
  }
  else if (id == 8) {
    fStage  = "ts4:sim";
    fIStage = "ts3:mubeam";
  }
  else if (id == 9) {
    fStage  = "ts4:stn";
    fIStage = "ts4:tgtstops";
  }

   TGTabElement *tabel = fTab->GetTabTab(id);

  if (fActiveTab != tabel) {
    fActiveTab->ChangeBackground(fTabColor);
    tabel->ChangeBackground(fYellow);
    fActiveTab = tabel;
  }

  printf("stage: %s  istage: %s\n",fStage.Data(),fIStage.Data());
}


void TestTabbed::BuildGui(const TGWindow *Parent, UInt_t Width, UInt_t Height) {

//-----------------------------------------------------------------------------
// main frame
//-----------------------------------------------------------------------------
   fMainFrame = new TGMainFrame(gClient->GetRoot(),Width,Height,kMainFrame | kVerticalFrame);
   fMainFrame->SetName("MainFrame");
   fMainFrame->SetLayoutBroken(kTRUE);


   // tab widget
   fTab = new TGTab(fMainFrame,320,40);
   fTab->Connect("Selected(Int_t)", "TestTabbed", this, "DoTab(Int_t)");

   // tab#1: container of "gen:50_200000"
   fFrame[0] = fTab->AddTab("gen:50_200000");
   fFrame[0]->SetLayoutManager(new TGVerticalLayout(fFrame[0]));

   TGTextButton *fTextButton = new TGTextButton(fFrame[0],"gen_fcl",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(10,20,200,24);
   fFrame[0]->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TJobSub", this, "gen_fcl()");


   // tab#2 : "s1:sim"
   fFrame[1] = fTab->AddTab("s1:sim");
   fFrame[1]->SetLayoutManager(new TGVerticalLayout(fFrame[1]));

   // container of "Tab3"
   fFrame[2] = fTab->AddTab("s2:sim");
   fFrame[2]->SetLayoutManager(new TGVerticalLayout(fFrame[2]));

   fFrame[3] = fTab->AddTab("s3:sim");
   fFrame[3]->SetLayoutManager(new TGVerticalLayout(fFrame[3]));

   fFrame[4] = fTab->AddTab("s3:stn");
   fFrame[4]->SetLayoutManager(new TGVerticalLayout(fFrame[4]));

   fFrame[5] = fTab->AddTab("ts1:sim");
   fFrame[5]->SetLayoutManager(new TGVerticalLayout(fFrame[5]));

   fFrame[6] = fTab->AddTab("ts2:sim");
   fFrame[6]->SetLayoutManager(new TGVerticalLayout(fFrame[6]));

   fFrame[7] = fTab->AddTab("ts3:sim");
   fFrame[7]->SetLayoutManager(new TGVerticalLayout(fFrame[7]));

   fFrame[8] = fTab->AddTab("ts4:sim");
   fFrame[8]->SetLayoutManager(new TGVerticalLayout(fFrame[8]));

   fFrame[9] = fTab->AddTab("ts4:stn");
   fFrame[9]->SetLayoutManager(new TGVerticalLayout(fFrame[9]));


   fTab->SetTab(0);
   fActiveTab = fTab->GetTabTab(0);

   fTabColor = fActiveTab->GetBackground();

   gClient->GetColorByName("yellow", fYellow);

   fActiveTab->ChangeBackground(fYellow);

   fMainFrame->AddFrame(fTab, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTab->MoveResize(20,20,560,260);


   fMainFrame->SetMWMHints(kMWMDecorAll,
			   kMWMFuncAll,
			   kMWMInputModeless);
   fMainFrame->MapSubwindows();

   fMainFrame->Resize(fMainFrame->GetDefaultSize());
   fMainFrame->MapWindow();
   fMainFrame->Resize(600,300);
}


//-----------------------------------------------------------------------------
void test_tabbed() {
  TestTabbed* x = new TestTabbed(gClient->GetRoot(),150,300);
}  
