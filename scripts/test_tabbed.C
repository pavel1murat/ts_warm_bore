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

  struct StageData_t {
    TString fStage;
    TString fInputDs;
    TString fTime;
  };

  TGMainFrame*        fMainFrame;
  TGTab *fTab ;

  TString             fProject;
  TString             fDsid;

  TString             fStage;
  TString             fIStage;

  TGCompositeFrame*   fFrame[100];
  TGTabElement*       fActiveTab;

  Pixel_t             fYellow;
  Pixel_t             fTabColor;

  StageData_t         fStageData[9];
  StageData_t*        fActiveStage;
  
  TestTabbed(const TGWindow *p, UInt_t w, UInt_t h);
  virtual ~TestTabbed();

  void     DoTab(Int_t id);

  void     BuildTabElement(TGTab*& Tab, TGCompositeFrame*& TabElement, StageData_t* StageData);

  void     BuildGui(const TGWindow *Parent, UInt_t Width, UInt_t Height);

}; 

//-----------------------------------------------------------------------------
TestTabbed::TestTabbed(const TGWindow *p, UInt_t w, UInt_t h) {
  fProject = "ts_warm_bore";
  fDsid    = "760_1000";

  fStageData[0] = StageData_t{"s1:sim" ,"gen:50_20000","10h"};
  fStageData[1] = StageData_t{"s2:sim" ,"s1:mubeam"   ,"10h"};
  fStageData[2] = StageData_t{"s3:sim" ,"s2:mubeam"   ,"10h"};
  fStageData[3] = StageData_t{"s3:stn" ,"s3:tgtstops" ,"10h"};

  fStageData[4] = StageData_t{"ts1:sim","pbar:vd91"   ,"10h"};
  fStageData[5] = StageData_t{"ts2:sim","ts1:mubeam"  ,"10h"};
  fStageData[6] = StageData_t{"ts3:sim","ts2:mubeam"  ,"10h"};
  fStageData[7] = StageData_t{"ts4:sim","ts3:mubeam"  ,"10h"};
  fStageData[8] = StageData_t{"ts4:stn","ts4:tgtstops","10h"};

  BuildGui(p,w,h);
}

//-----------------------------------------------------------------------------
TestTabbed::~TestTabbed() {
   fMainFrame->Cleanup();
}


//-----------------------------------------------------------------------------
// set new active tab
//-----------------------------------------------------------------------------
void TestTabbed::DoTab(Int_t id) {

  TGTabElement *tabel = fTab->GetTabTab(id);

  if (fActiveTab != tabel) {
    fActiveTab->ChangeBackground(fTabColor);
    tabel->ChangeBackground(fYellow);
    fActiveTab = tabel;
  }

  fActiveStage = &fStageData[id];
  printf("Tab ID: %3i stage: %s  istage: %s title: %s\n",
	 id,
	 fActiveStage->fStage.Data(),
	 fActiveStage->fInputDs.Data(),
	 fActiveTab->GetText()->Data());
}


//-----------------------------------------------------------------------------
void TestTabbed::BuildTabElement(TGTab*& Tab, TGCompositeFrame*& TabElement, StageData_t* StageData) {

  const char* title=StageData->fStage.Data();
  const char* input=StageData->fInputDs.Data();

  printf("[TestTabbed::BuildTabElement] title: %s\n",title);

  TabElement = Tab->AddTab(title);
  TabElement->SetLayoutManager(new TGVerticalLayout(TabElement));
  TabElement->SetLayoutBroken(kTRUE);

  TGGroupFrame* group = new TGGroupFrame(TabElement,Form("%s:%s stage: %s",fProject.Data(),fDsid.Data(),title));
  //  group->SetLayoutManager(new TGVerticalLayout(group));
  group->SetLayoutBroken(kTRUE);
  
  TGLabel* label = new TGLabel(group,Form("%s:%s    %s   %s",fProject.Data(),fDsid.Data(),title,input));
  label->SetTextJustify(16);
  label->SetMargins(0,0,0,0);
  label->SetWrapLength(-1);
  group->AddFrame(label, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  label->MoveResize(20,20,380,24);
  
  TabElement->AddFrame(group, new TGLayoutHints(kLHintsNormal));
  group->MoveResize(10,10,445,70);
}

void TestTabbed::BuildGui(const TGWindow *Parent, UInt_t Width, UInt_t Height) {

//-----------------------------------------------------------------------------
// main frame
//-----------------------------------------------------------------------------
   fMainFrame = new TGMainFrame(gClient->GetRoot(),Width,Height,kMainFrame | kVerticalFrame);
   fMainFrame->SetName("MainFrame");
   fMainFrame->SetLayoutBroken(kTRUE);
//-----------------------------------------------------------------------------
// add multiple tabs widget
//-----------------------------------------------------------------------------
   fTab = new TGTab(fMainFrame,320,40);
   fMainFrame->AddFrame(fTab, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

   BuildTabElement(fTab,fFrame[0],&fStageData[0]);
   BuildTabElement(fTab,fFrame[1],&fStageData[1]);
   BuildTabElement(fTab,fFrame[2],&fStageData[2]);
   BuildTabElement(fTab,fFrame[3],&fStageData[3]);

   BuildTabElement(fTab,fFrame[4],&fStageData[4]);
   BuildTabElement(fTab,fFrame[5],&fStageData[5]);
   BuildTabElement(fTab,fFrame[6],&fStageData[6]);
   BuildTabElement(fTab,fFrame[7],&fStageData[7]);
   BuildTabElement(fTab,fFrame[8],&fStageData[8]);

   fTab->MoveResize(10,10,470,110);
   fTab->Connect("Selected(Int_t)", "TestTabbed", this, "DoTab(Int_t)");
//-----------------------------------------------------------------------------
// buttons - common , they do not change
//-----------------------------------------------------------------------------
   int y0        = 125;
   int button_sy =  30;
//-----------------------------------------------------------------------------
// gen_fcl and submit_grid_job
//-----------------------------------------------------------------------------
   TGTextButton* fTextButton = new TGTextButton(fMainFrame,"gen_fcl",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(10,y0,150,25);
   fMainFrame->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TJobSub", this, "gen_fcl()");

   fTextButton = new TGTextButton(fMainFrame,"submit_grid_job",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(10,y0+1*button_sy,150,25);
   fMainFrame->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TJobSub", this, "submit_grid_job()");
//-----------------------------------------------------------------------------
// check_grid_output etc
//-----------------------------------------------------------------------------
   fTextButton = new TGTextButton(fMainFrame,"check_grid_output",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(170,y0,150,25);
   fMainFrame->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TJobSub", this, "check_grid_output()");

   fTextButton = new TGTextButton(fMainFrame,"move_stage_output",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(170,y0+button_sy,150,25);
   fMainFrame->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TJobSub", this, "move_stage_output()");

   fTextButton = new TGTextButton(fMainFrame,"list_pnfs_files",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(170,y0+button_sy*2,150,25);
   fMainFrame->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TJobSub", this, "list_pnfs_files()");

   fTextButton = new TGTextButton(fMainFrame,"jobsub_q",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(170,y0+button_sy*3,150,25);
   fMainFrame->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TJobSub", this, "jobsub_q()");  
//-----------------------------------------------------------------------------
// submit_stnmaker_job and catalog_stntuples
//-----------------------------------------------------------------------------
   fTextButton = new TGTextButton(fMainFrame,"submit_stnmaker_job",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(330,y0,150,25);
   fMainFrame->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TJobSub", this, "submit_stnmaker_job()");

   fTextButton = new TGTextButton(fMainFrame,"catalog_stntuples",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(330,y0+button_sy,150,25);
   fMainFrame->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TJobSub", this, "catalog_stntuples()");
//-----------------------------------------------------------------------------
// set active tab
//-----------------------------------------------------------------------------
   fTab->SetTab(0);
   fActiveTab = fTab->GetTabTab(0);
   fTabColor  = fActiveTab->GetBackground();

   gClient->GetColorByName("yellow", fYellow);
   fActiveTab->ChangeBackground(fYellow);

   fMainFrame->SetMWMHints(kMWMDecorAll,
			   kMWMFuncAll,
			   kMWMInputModeless);
   fMainFrame->MapSubwindows();

   fMainFrame->Resize(fMainFrame->GetDefaultSize());
   fMainFrame->MapWindow();
   fMainFrame->Resize(490,y0+4*button_sy);
}


//-----------------------------------------------------------------------------
void test_tabbed() {
  TestTabbed* x = new TestTabbed(gClient->GetRoot(),150,300);
}  
