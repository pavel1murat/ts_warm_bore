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
    TString fXRootd;
    TString fExtras;
  };

  struct MyTabElement_t {
    TGCompositeFrame*   fFrame;
    TGTextEntry*        fTime;
    TGTextEntry*        fExtras;
  };

  TGMainFrame*        fMainFrame;
  TGTab *fTab ;

  TString             fProject;
  TString             fDsid;

  TString             fStage;
  TString             fIStage;
  TString             fTime;
  TString             fExtraParameters;

  TGTabElement*       fActiveTab;

  MyTabElement_t      fTabElement[100];
  int                 fNTabElements;
  int                 fActiveTabID;

  Pixel_t             fYellow;		// active tab tip
  Pixel_t             fTabColor;	// non-active tab tip

  StageData_t         fStageData[100];
  StageData_t*        fActiveStage;

  int                 fDebugLevel;
  
  TestTabbed(const char* Dsid, const TGWindow *p, UInt_t w, UInt_t h, int DebugLevel = 0);
  virtual ~TestTabbed();

  void     DoTab          (Int_t id);
  void     BuildTabElement(TGTab*& Tab, MyTabElement_t& TabElement, StageData_t* StageData);
  void     BuildGui       (const TGWindow *Parent, UInt_t Width, UInt_t Height);

  void     ExecuteCommand(const char* Cmd, int PrintOnly = 0);

  void     build_tarball      ();
  void     check_grid_output  ();
  void     list_pnfs_files    ();
  void     move_stage_output  ();
  void     move_dset_to_dcache();

  void     submit_stnmaker_job();
  void     catalog_stntuples  ();

  void     gen_fcl();
  void     submit_grid_job();
  void     jobsub_q();

}; 


//-----------------------------------------------------------------------------
// initialization with the project data - in its rudimentary form
//-----------------------------------------------------------------------------
TestTabbed::TestTabbed(const char* Dsid, const TGWindow *p, UInt_t w, UInt_t h, int DebugLevel) {

  fProject      = "ts_warm_bore";
  fDsid         = Dsid;
  fDebugLevel   = DebugLevel;

  fStageData[0] = StageData_t{"s1:sim" ,"gen:50_20000","10h","xrootd","."};
  fStageData[1] = StageData_t{"s2:sim" ,"s1:mubeam"   ,"10h","xrootd","."};
  fStageData[2] = StageData_t{"s3:sim" ,"s2:mubeam"   ,"10h","xrootd","."};
  fStageData[3] = StageData_t{"s3:stn" ,"s3:tgtstops" ,"10h","xrootd","."};

  fStageData[4] = StageData_t{"ts1:sim","pbar:vd91"   ,"10h","xrootd","."};
  fStageData[5] = StageData_t{"ts2:sim","ts1:mubeam"  ,"10h","xrootd","."};
  fStageData[6] = StageData_t{"ts3:sim","ts2:mubeam"  ,"10h","xrootd","."};
  fStageData[7] = StageData_t{"ts3:stn","ts3:mubeam"  ,"10h","xrootd","."};
  fStageData[8] = StageData_t{"ts4:sim","ts3:mubeam"  ,"10h","xrootd","."};
  fStageData[9] = StageData_t{"ts4:stn","ts4:tgtstops","10h","xrootd","."};

  fNTabElements = 10;  // 0:9

  BuildGui(p,w,h);
}

//-----------------------------------------------------------------------------
TestTabbed::~TestTabbed() {
   fMainFrame->Cleanup();
}


//-----------------------------------------------------------------------------
void TestTabbed::ExecuteCommand(const char* Cmd, int PrintOnly) {
  printf(">> TestTabbed::ExecuteCommand : executing cmd: %s\n",Cmd);

  if (PrintOnly != 1) {
    char buf[10001];
    FILE* pipe = gSystem->OpenPipe(Cmd,"r");
    while (fgets(buf,10000,pipe)) { printf("%s",buf); }
    gSystem->ClosePipe(pipe);
  }

  printf(">> TestTabbed::ExecuteCommand : DONE\n");
}

//-----------------------------------------------------------------------------
void TestTabbed::build_tarball() {
  TString cmd;

  // ts_warm_bore/scripts/grid_job.py --verbose=1 --project=ts_warm_bore --dsid=760_1022 --stage=ts2_sim  --job=build_tarball


  cmd = Form("%s/scripts/grid_job.py --verbose=1 --project=%s --dsid=%s --stage=%s --job=build_tarball",
	     fProject.Data(),
	     fProject.Data(),
	     fDsid.Data(),
	     fStage.Data());

  int print_only=1;                           // start from debugging
  ExecuteCommand(cmd.Data(),print_only);
}

//-----------------------------------------------------------------------------
void TestTabbed::move_dset_to_dcache() {
  TString cmd;

  cmd = Form("%s/scripts/move_dset_to_dcache %s %s %s %s .: NOT IMPLEMENTED YET!",
	     fProject.Data(),
	     fProject.Data(),
	     fDsid.Data(),
	     fIStage.Data(),
	     fStage.Data());

  int print_only = 1;
  ExecuteCommand(cmd.Data(),print_only);
}

//-----------------------------------------------------------------------------
// check grid output
//-----------------------------------------------------------------------------
void TestTabbed::check_grid_output() {
  TString cmd;

  MyTabElement_t* tab = fTabElement+fActiveTabID;
  
  cmd = Form("%s/scripts/check_grid_output %s %s %s %s %s",
	     fProject.Data(),
	     fProject.Data(),
	     fDsid.Data(),
	     fActiveStage->fInputDs.Data(),
	     fActiveStage->fStage.Data(),
	     tab->fExtras->GetText());

  ExecuteCommand(cmd.Data(),fDebugLevel);
}

//-----------------------------------------------------------------------------
void TestTabbed::move_stage_output() {
  TString cmd;

  MyTabElement_t* tab = fTabElement+fActiveTabID;

  cmd = Form("%s/scripts/move_stage_output %s %s %s %s %s",
	     fProject.Data(),
	     fProject.Data(),
	     fDsid.Data(),
	     fActiveStage->fInputDs.Data(),
	     fActiveStage->fStage.Data(),
	     tab->fExtras->GetText());

  ExecuteCommand(cmd.Data(),fDebugLevel);
}

//-----------------------------------------------------------------------------
// list PNFS files
//-----------------------------------------------------------------------------
void TestTabbed::list_pnfs_files() {
  TString cmd;

  MyTabElement_t* tab = fTabElement+fActiveTabID;

  cmd = Form("%s/scripts/list_pnfs_files %s %s %s %s %s",
	     fProject.Data(),
	     fProject.Data(),
	     fDsid.Data(),
	     fActiveStage->fInputDs.Data(),
	     fActiveStage->fStage.Data(),
	     tab->fExtras->GetText());

  ExecuteCommand(cmd.Data(),fDebugLevel);
}

//-----------------------------------------------------------------------------
// check grid output
//-----------------------------------------------------------------------------
void TestTabbed::jobsub_q() {
  TString cmd;

  cmd = Form("date; time jobsub_q --user murat");

  ExecuteCommand(cmd.Data(),fDebugLevel);
}

//-----------------------------------------------------------------------------
// generate fcl
//-----------------------------------------------------------------------------
void TestTabbed::gen_fcl() {
  TString cmd;

  MyTabElement_t* tab = fTabElement+fActiveTabID;

  cmd = Form("%s/scripts/gen_fcl %s %s %s %s .",
	     fProject.Data(),
	     fProject.Data(),
	     fDsid.Data(),
	     fActiveStage->fInputDs.Data(),
	     fActiveStage->fStage.Data());

  ExecuteCommand(cmd.Data(),fDebugLevel);
}

//-----------------------------------------------------------------------------
void TestTabbed::submit_grid_job() {
  TString cmd;

  MyTabElement_t* tab = fTabElement+fActiveTabID;

  cmd = Form("%s/scripts/submit_grid_job %s %s %s %s %s .",
	     fProject.Data(),
	     fProject.Data(),
	     fDsid.Data(),
	     fActiveStage->fInputDs.Data(),
	     fActiveStage->fStage.Data(),
	     tab->fTime->GetText());

  TDatime x;
  TString istage = fIStage.Data();
  TString jstage = fStage.Data();
  TString time   = fTime.Data();

  istage.ReplaceAll(':','_');
  jstage.ReplaceAll(':','_');

  printf("* <%s> * SUBMITTED* : %s.%s.%s.%s      %s \n",x.AsSQLString(),fProject.Data(),fDsid.Data(),fActiveStage->fInputDs.Data(),fActiveStage->fStage.Data(),tab->fTime->GetText());

  ExecuteCommand(cmd.Data(),fDebugLevel);
}

//-----------------------------------------------------------------------------
// so far, assume running interactively, otherwise - submit grid job 
//-----------------------------------------------------------------------------
void TestTabbed::submit_stnmaker_job() {
  TString cmd;

  cmd = Form("%s/scripts/submit_stnmaker_job %s %s %s %s .",
	     fProject.Data(),
	     fProject.Data(),
	     fDsid.Data(),
	     fIStage.Data(),
	     fStage.Data());

  // TDatime x;
  // TString istage = fGui.fInputStage->GetText();
  // TString jstage = fGui.fStage->GetText();

  // istage.ReplaceAll(':','_');
  // jstage.ReplaceAll(':','_');
  //
  //  printf("* <%s> * SUBMITTED* : %s.%s.%s.%s      %s \n",x.AsSQLString(),fProject.Data(),fDsid.Data(),istage.Data(),jstage.Data(),fGui.fTime->GetText());

  ExecuteCommand(cmd.Data());
}

//-----------------------------------------------------------------------------
// so far, always an interactive command
//-----------------------------------------------------------------------------
void TestTabbed::catalog_stntuples() {
  TString cmd;


  //  Stntuple/scripts/catalog_stntuples --bluearc -b ts_warm_bore -d ${dsid}_s3_tgtstops -p .nts.murat -D /mu2e/data/users/murat/datasets/ts_warm_bore/$dsid/s3_stn_tgtstops --install  ;

  TString istage = fStage.Data();
  istage.ReplaceAll(':','_');

  TObjArray* ist           = istage.Tokenize("_");
  TString    input_stage   = ((TObjString*) ist->At(0))->GetString().Data();
  TString    input_dataset = ((TObjString*) ist->At(1))->GetString().Data();

  TString jstage = fStage.Data();
  jstage.ReplaceAll(':','_');

  TObjArray* jst       = jstage.Tokenize("_");
  TString    job_stage = ((TObjString*) jst->At(0))->GetString().Data();
  TString    job_type  = ((TObjString*) jst->At(1))->GetString().Data();

  printf("input_stage: %s input_dataset: %s job_stage: %s job_type: %s\n",
	 input_stage.Data(),input_dataset.Data(),
	 job_stage.Data(),job_type.Data());
	 

  cmd = Form("Stntuple/scripts/catalog_stntuples --bluearc -b %s -d %s_%s -p nts.murat -D /mu2e/data/users/murat/datasets/%s/%s/%s_%s_%s --install %s",
	     fProject.Data(),
	     fDsid.Data(),
	     istage.Data(),
	     fProject.Data(),
	     fDsid.Data(),
	     job_stage.Data(),
	     job_type.Data(),
	     input_dataset.Data(),
	     "/publicweb/m/murat/cafdfc");

  int print_only = 0; // debug first !
  ExecuteCommand(cmd.Data(),print_only);
}

//-----------------------------------------------------------------------------
// set new active tab
//-----------------------------------------------------------------------------
void TestTabbed::DoTab(Int_t id) {


  if (id != fActiveTabID) {

    TGTabElement *tabel = fTab->GetTabTab(id);

    if (fActiveTab != tabel) {
      fActiveTab->ChangeBackground(fTabColor);
      tabel->ChangeBackground(fYellow);
      fActiveTab = tabel;
    }

    fActiveTabID = id;
    fActiveStage = &fStageData[id];
  }

  printf("Tab ID: %3i stage: %-15s istage: %-15s time: %-15s extras: %-15s title: %-15s\n",
	 id,
	 fActiveStage->fStage.Data(),
	 fActiveStage->fInputDs.Data(),
	 fTabElement[id].fTime->GetText(),
	 fTabElement[id].fExtras->GetText(),
	 fActiveTab->GetText()->Data());
}


//-----------------------------------------------------------------------------
void TestTabbed::BuildTabElement(TGTab*& Tab, MyTabElement_t& TabElement, StageData_t* StageData) {

  const char* title=StageData->fStage.Data();
  const char* input=StageData->fInputDs.Data();

  //  printf("[TestTabbed::BuildTabElement] title: %s\n",title);

  TabElement.fFrame = Tab->AddTab(title);
  TabElement.fFrame->SetLayoutManager(new TGVerticalLayout(TabElement.fFrame));
  TabElement.fFrame->SetLayoutBroken(kTRUE);

  TGGroupFrame* group = new TGGroupFrame(TabElement.fFrame,Form("%s:%s stage: %s %s parameters",fProject.Data(),fDsid.Data(),title,input));
  //  group->SetLayoutManager(new TGVerticalLayout(group));
  group->SetLayoutBroken(kTRUE);
//-----------------------------------------------------------------------------
// "time:xrootd" label
//-----------------------------------------------------------------------------
  TGLabel* label = new TGLabel(group,Form("time:xrootd"));
  label->SetTextJustify(1);
  label->SetMargins(0,0,0,0);
  label->SetWrapLength(-1);
  group->AddFrame(label, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  label->MoveResize(20,25,60,25);
//-----------------------------------------------------------------------------
// "time:xrootd" text entry
//-----------------------------------------------------------------------------
  TGFont *ufont;         // will reflect user font changes
  ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

  TGGC   *uGC;                          // will reflect user GC changes

					// graphics context changes
  GCValues_t valEntry_uGC;
  valEntry_uGC.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
  gClient->GetColorByName("#000000",valEntry_uGC.fForeground);
  gClient->GetColorByName("#e8e8e8",valEntry_uGC.fBackground);
  valEntry_uGC.fFillStyle = kFillSolid;
  valEntry_uGC.fFont = ufont->GetFontHandle();
  valEntry_uGC.fGraphicsExposures = kFALSE;
  uGC = gClient->GetGC(&valEntry_uGC, kTRUE);
  
  TabElement.fTime = new TGTextEntry(group, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
  TabElement.fTime->SetMaxLength(4096);
  TabElement.fTime->SetAlignment(kTextLeft);
  TabElement.fTime->SetText("3h:xrootd");
  TabElement.fTime->Resize(112,TabElement.fTime->GetDefaultHeight());
  group->AddFrame(TabElement.fTime, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  TabElement.fTime->MoveResize(90,25,70,25);
//-----------------------------------------------------------------------------
// "extras" label and text entry
//-----------------------------------------------------------------------------
  label = new TGLabel(group,Form("extras"));
  label->SetTextJustify(1);
  label->SetMargins(0,0,0,0);
  label->SetWrapLength(-1);
  group->AddFrame(label, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  label->MoveResize(180,25,60,25);

  TabElement.fExtras = new TGTextEntry(group, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
  TabElement.fExtras->SetMaxLength(4096);
  TabElement.fExtras->SetAlignment(kTextLeft);
  TabElement.fExtras->SetText(" . ");
  TabElement.fExtras->Resize(112,TabElement.fExtras->GetDefaultHeight());
  group->AddFrame(TabElement.fExtras, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
  TabElement.fExtras->MoveResize(250,25,70,25);
//-----------------------------------------------------------------------------
// finish composition of the tab element
//-----------------------------------------------------------------------------
  TabElement.fFrame->AddFrame(group, new TGLayoutHints(kLHintsNormal));
  group->MoveResize(10,10,445,70);
}

void TestTabbed::BuildGui(const TGWindow *Parent, UInt_t Width, UInt_t Height) {

//-----------------------------------------------------------------------------
// main frame
//-----------------------------------------------------------------------------
   fMainFrame = new TGMainFrame(gClient->GetRoot(),Width,Height,kMainFrame | kVerticalFrame);
   fMainFrame->SetLayoutBroken(kTRUE);
   fMainFrame->SetWindowName(Form("%s:%s",fProject.Data(),fDsid.Data()));
   fMainFrame->SetName("MainFrame");
//-----------------------------------------------------------------------------
// add tab holder and multiple tabs (tab elements) 
//-----------------------------------------------------------------------------
   fTab = new TGTab(fMainFrame,320,40);
   fMainFrame->AddFrame(fTab, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

   for (int i=0; i<fNTabElements; i++) {
     BuildTabElement(fTab,fTabElement[i],&fStageData[i]);
   }

   fTab->MoveResize(10,10,470,110);
   fTab->Connect("Selected(Int_t)", "TestTabbed", this, "DoTab(Int_t)");
//-----------------------------------------------------------------------------
// buttons - common , they do not change
//-----------------------------------------------------------------------------
   int y0        = 125;
   int button_dx = 150;
   int button_sx = 150+10;
   int button_sy =  30;
//-----------------------------------------------------------------------------
// gen_fcl and submit_grid_job
//-----------------------------------------------------------------------------
   TGTextButton* fTextButton = new TGTextButton(fMainFrame,"build_tarball",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(10,y0,button_dx,25);
   fMainFrame->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TestTabbed", this, "build_tarball()");

   fTextButton = new TGTextButton(fMainFrame,"gen_fcl",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(10,y0+button_sy,button_dx,25);
   fMainFrame->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TestTabbed", this, "gen_fcl()");

   fTextButton = new TGTextButton(fMainFrame,"submit_grid_job",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(10,y0+2*button_sy,button_dx,25);
   fMainFrame->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TestTabbed", this, "submit_grid_job()");

   fTextButton = new TGTextButton(fMainFrame,"jobsub_q",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(10,y0+button_sy*3,button_dx,25);
   fMainFrame->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TestTabbed", this, "jobsub_q()");  
//-----------------------------------------------------------------------------
// check_grid_output etc
//-----------------------------------------------------------------------------
   fTextButton = new TGTextButton(fMainFrame,"check_grid_output",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(10+button_sx,y0,button_dx,25);
   fMainFrame->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TestTabbed", this, "check_grid_output()");

   fTextButton = new TGTextButton(fMainFrame,"move_stage_output",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(10+button_sx,y0+button_sy,150,25);
   fMainFrame->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TestTabbed", this, "move_stage_output()");

   fTextButton = new TGTextButton(fMainFrame,"list_pnfs_files",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(10+button_sx,y0+button_sy*2,150,25);
   fMainFrame->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TestTabbed", this, "list_pnfs_files()");
//-----------------------------------------------------------------------------
// submit_stnmaker_job and catalog_stntuples
//-----------------------------------------------------------------------------
   fTextButton = new TGTextButton(fMainFrame,"submit_stnmaker_job",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(10+2*button_sx,y0,150,25);
   fMainFrame->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TestTabbed", this, "submit_stnmaker_job()");

   fTextButton = new TGTextButton(fMainFrame,"catalog_stntuples",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->MoveResize(10+2*button_sx,y0+button_sy,150,25);
   fMainFrame->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TestTabbed", this, "catalog_stntuples()");
//-----------------------------------------------------------------------------
// set active tab
//-----------------------------------------------------------------------------
   fActiveTabID = 0;
   fTab->SetTab(fActiveTabID);

   fActiveTab = (TGTabElement*) fTabElement[fActiveTabID].fFrame; // fTab->GetTabTab(0);
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
void test_tabbed(const char* Dsid, int DebugLevel = 0) {
  TestTabbed* x = new TestTabbed(Dsid,gClient->GetRoot(),150,300,DebugLevel);
}  
