// Mainframe macro generated from application: root.exe
// By ROOT version 6.18/04 on 2020-05-09 22:50:02

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
#ifndef ROOT_TGMsgBox
#include "TGMsgBox.h"
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


class TJobSub {

private:

  TGMainFrame*        fMainFrame;

  struct Gui_t {
    TGTextEntry*   fProject;
    TGTextEntry*   fDsid;
    TGTextEntry*   fInputStage;
    TGTextEntry*   fStage;
    TGTextEntry*   fTime;
    TGTextEntry*   fExtraParameters;
  } fGui;




public:
  TJobSub(const TGWindow *p, UInt_t w, UInt_t h);

  virtual ~TJobSub();

  void     BuildGui(const TGWindow *Parent, UInt_t Width, UInt_t Height);
  void     ExecuteCommand(const char* Cmd);

  void     gridexport();

  void     CheckGridOutput();

  void     list_pnfs_files();

  void     move_stage_output();
  void     gen_fcl();
  void     submit_grid_job();
  void     jobsub_q();
  
  ClassDef(TJobSub, 0)
};

//-----------------------------------------------------------------------------
TJobSub::TJobSub(const TGWindow *p, UInt_t w, UInt_t h) {
  BuildGui(p, w, h);
}

//-----------------------------------------------------------------------------
TJobSub::~TJobSub() {
   fMainFrame->Cleanup();
}

//-----------------------------------------------------------------------------
void TJobSub::ExecuteCommand(const char* Cmd) {
  printf(">> TJobSub::ExecuteCommand : executing cmd: %s\n",Cmd);
  char buf[512];
  FILE* pipe = gSystem->OpenPipe(Cmd,"r");
  while (fgets(buf,10000,pipe)) { printf("%s",buf); }
  gSystem->ClosePipe(pipe);

  printf(">> TJobSub::ExecuteCommand : DONE\n");
}

//-----------------------------------------------------------------------------
void TJobSub::move_stage_output() {
  TString cmd;

  cmd = Form("%s/scripts/move_stage_output %s %s %s %s .",
	     fGui.fProject->GetText(),
	     fGui.fProject->GetText(),
	     fGui.fDsid->GetText(),
	     fGui.fInputStage->GetText(),
	     fGui.fStage->GetText());

  ExecuteCommand(cmd.Data());
}

//-----------------------------------------------------------------------------
// check grid output
//-----------------------------------------------------------------------------
void TJobSub::CheckGridOutput() {
  TString cmd;

  cmd = Form("%s/scripts/check_grid_output %s %s %s %s %s",
	     fGui.fProject->GetText(),
	     fGui.fProject->GetText(),
	     fGui.fDsid->GetText(),
	     fGui.fInputStage->GetText(),
	     fGui.fStage->GetText(),
	     fGui.fExtraParameters->GetText());

  ExecuteCommand(cmd.Data());
}

//-----------------------------------------------------------------------------
// check grid output
//-----------------------------------------------------------------------------
void TJobSub::list_pnfs_files() {
  TString cmd;

  cmd = Form("%s/scripts/list_pnfs_files %s %s %s %s %s",
	     fGui.fProject->GetText(),
	     fGui.fProject->GetText(),
	     fGui.fDsid->GetText(),
	     fGui.fInputStage->GetText(),
	     fGui.fStage->GetText(),
	     fGui.fExtraParameters->GetText());

  ExecuteCommand(cmd.Data());
}

//-----------------------------------------------------------------------------
// check grid output
//-----------------------------------------------------------------------------
void TJobSub::jobsub_q() {
  TString cmd;

  cmd = Form("date; time jobsub_q --user murat");

  ExecuteCommand(cmd.Data());
}

//-----------------------------------------------------------------------------
// generate fcl
//-----------------------------------------------------------------------------
void TJobSub::gen_fcl() {
  TString cmd;

  cmd = Form("%s/scripts/gen_fcl %s %s %s %s .",
	     fGui.fProject->GetText(),
	     fGui.fProject->GetText(),
	     fGui.fDsid->GetText(),
	     fGui.fInputStage->GetText(),
	     fGui.fStage->GetText());

  ExecuteCommand(cmd.Data());
}

//-----------------------------------------------------------------------------
void TJobSub::submit_grid_job() {
  // printf("TJobSub::submit_grid_job(): about to call submit_grid_job project=%s dsid=%s\n",fProject->GetText(),fDsid->GetText());
  TString cmd;

  cmd = Form("%s/scripts/submit_grid_job %s %s %s %s %s .",
	     fGui.fProject->GetText(),
	     fGui.fProject->GetText(),
	     fGui.fDsid->GetText(),
	     fGui.fInputStage->GetText(),
	     fGui.fStage->GetText(),
	     fGui.fTime->GetText());

  ExecuteCommand(cmd.Data());
}

//-----------------------------------------------------------------------------
void TJobSub::BuildGui(const TGWindow *Parent, UInt_t Width, UInt_t Height) {
//-----------------------------------------------------------------------------
// main frame
//-----------------------------------------------------------------------------
   fMainFrame = new TGMainFrame(gClient->GetRoot(),Width,Height,kMainFrame | kVerticalFrame);
   fMainFrame->SetName("MainFrame");
   fMainFrame->SetLayoutBroken(kTRUE);
//-----------------------------------------------------------------------------
// left subframe - labels and text entries
//-----------------------------------------------------------------------------
   // "fGroupFrameParameters" group frame
   TGGroupFrame *fGroupFrameParameters = new TGGroupFrame(fMainFrame,"Parameters");
   fGroupFrameParameters->SetLayoutBroken(kTRUE);

   TGLabel *fLabel1910 = new TGLabel(fGroupFrameParameters,"Project");
   fLabel1910->SetTextJustify(36);
   fLabel1910->SetMargins(0,0,0,0);
   fLabel1910->SetWrapLength(-1);
   fGroupFrameParameters->AddFrame(fLabel1910, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fLabel1910->MoveResize(24,32,72,30);

   TGLabel *fLabel1933 = new TGLabel(fGroupFrameParameters,"DsID");
   fLabel1933->SetTextJustify(36);
   fLabel1933->SetMargins(0,0,0,0);
   fLabel1933->SetWrapLength(-1);
   fGroupFrameParameters->AddFrame(fLabel1933, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fLabel1933->MoveResize(16,80,80,30);

   TGLabel *fLabel1948 = new TGLabel(fGroupFrameParameters,"Input Stage");
   fLabel1948->SetTextJustify(36);
   fLabel1948->SetMargins(0,0,0,0);
   fLabel1948->SetWrapLength(-1);
   fGroupFrameParameters->AddFrame(fLabel1948, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fLabel1948->MoveResize(32,140,64,25);

   TGLabel *fLabel1955 = new TGLabel(fGroupFrameParameters,"Stage");
   fLabel1955->SetTextJustify(36);
   fLabel1955->SetMargins(0,0,0,0);
   fLabel1955->SetWrapLength(-1);
   fGroupFrameParameters->AddFrame(fLabel1955, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fLabel1955->MoveResize(32,200,72,24);

   TGLabel *fLabel1962 = new TGLabel(fGroupFrameParameters,"Time/xrootd");
   fLabel1962->SetTextJustify(36);
   fLabel1962->SetMargins(0,0,0,0);
   fLabel1962->SetWrapLength(-1);
   fGroupFrameParameters->AddFrame(fLabel1962, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fLabel1962->MoveResize(17,240,88,20);

   TGLabel *fLabel2027 = new TGLabel(fGroupFrameParameters,"Extra Parameters");
   fLabel2027->SetTextJustify(36);
   fLabel2027->SetMargins(0,0,0,0);
   fLabel2027->SetWrapLength(-1);
   fGroupFrameParameters->AddFrame(fLabel2027, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fLabel2027->MoveResize(24,288,88,24);
//-----------------------------------------------------------------------------
// text entries
//-----------------------------------------------------------------------------
   TGFont *ufont;         // will reflect user font changes
   ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

   TGGC   *uGC;           // will reflect user GC changes

					// graphics context changes
   GCValues_t valEntry_uGC;
   valEntry_uGC.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   gClient->GetColorByName("#000000",valEntry_uGC.fForeground);
   gClient->GetColorByName("#e8e8e8",valEntry_uGC.fBackground);
   valEntry_uGC.fFillStyle = kFillSolid;
   valEntry_uGC.fFont = ufont->GetFontHandle();
   valEntry_uGC.fGraphicsExposures = kFALSE;
   uGC = gClient->GetGC(&valEntry_uGC, kTRUE);

   fGui.fProject = new TGTextEntry(fGroupFrameParameters, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   fGui.fProject->SetMaxLength(4096);
   fGui.fProject->SetAlignment(kTextLeft);
   fGui.fProject->SetText("ts_warm_bore");
   fGui.fProject->Resize(104,fGui.fProject->GetDefaultHeight());
   fGroupFrameParameters->AddFrame(fGui.fProject, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fGui.fProject->MoveResize(120,32,112,22);

   fGui.fDsid = new TGTextEntry(fGroupFrameParameters, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   fGui.fDsid->SetMaxLength(4096);
   fGui.fDsid->SetAlignment(kTextLeft);
   fGui.fDsid->SetText("760_1000");
   fGui.fDsid->Resize(112,fGui.fDsid->GetDefaultHeight());
   fGroupFrameParameters->AddFrame(fGui.fDsid, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fGui.fDsid->MoveResize(120,80,112,22);

   fGui.fInputStage = new TGTextEntry(fGroupFrameParameters, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   fGui.fInputStage->SetMaxLength(4096);
   fGui.fInputStage->SetAlignment(kTextLeft);
   fGui.fInputStage->SetText("s1:mubeam");
   fGui.fInputStage->Resize(112,fGui.fInputStage->GetDefaultHeight());
   fGui.fInputStage->MoveResize(120,140,112,22);
   fGroupFrameParameters->AddFrame(fGui.fInputStage, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

   fGui.fStage = new TGTextEntry(fGroupFrameParameters, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   fGui.fStage->SetMaxLength(4096);
   fGui.fStage->SetAlignment(kTextLeft);
   fGui.fStage->SetText("s2:sim");
   fGui.fStage->Resize(112,fGui.fStage->GetDefaultHeight());
   fGroupFrameParameters->AddFrame(fGui.fStage, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fGui.fStage->MoveResize(120,200,112,22);

   fGui.fTime = new TGTextEntry(fGroupFrameParameters, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   fGui.fTime->SetMaxLength(4096);
   fGui.fTime->SetAlignment(kTextLeft);
   fGui.fTime->SetText("3h xrootd");
   fGui.fTime->Resize(112,fGui.fTime->GetDefaultHeight());
   fGroupFrameParameters->AddFrame(fGui.fTime, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fGui.fTime->MoveResize(120,240,112,22);

   fGui.fExtraParameters = new TGTextEntry(fGroupFrameParameters, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   fGui.fExtraParameters->SetMaxLength(4096);
   fGui.fExtraParameters->SetAlignment(kTextLeft);
   fGui.fExtraParameters->SetText(".");
   fGui.fExtraParameters->Resize(104,fGui.fExtraParameters->GetDefaultHeight());
   fGroupFrameParameters->AddFrame(fGui.fExtraParameters, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fGui.fExtraParameters->MoveResize(128,288,104,22);

   TGHorizontal3DLine *fHorizontal3DLine2566 = new TGHorizontal3DLine(fGroupFrameParameters,208,1);
   fGroupFrameParameters->AddFrame(fHorizontal3DLine2566, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fHorizontal3DLine2566->MoveResize(24,64,208,1);

   TGHorizontal3DLine *fHorizontal3DLine2579 = new TGHorizontal3DLine(fGroupFrameParameters,200,1);
   fGroupFrameParameters->AddFrame(fHorizontal3DLine2579, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fHorizontal3DLine2579->MoveResize(24,120,200,1);

   TGHorizontal3DLine *fHorizontal3DLine2704 = new TGHorizontal3DLine(fGroupFrameParameters,208,8);
   fGroupFrameParameters->AddFrame(fHorizontal3DLine2704, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fHorizontal3DLine2704->MoveResize(24,184,208,8);

   fGroupFrameParameters->SetLayoutManager(new TGVerticalLayout(fGroupFrameParameters));
   fGroupFrameParameters->Resize(250,360);
   fMainFrame->AddFrame(fGroupFrameParameters, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fGroupFrameParameters->MoveResize(30,20,250,360);

//-----------------------------------------------------------------------------
// central text entry group frame
//-----------------------------------------------------------------------------
   // // "fCentralFrame" group frame
   // TGGroupFrame *fCentralFrame = new TGGroupFrame(fMainFrame,"Central");
   // fCentralFrame->SetLayoutBroken(kTRUE);

   // ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

   // // graphics context changes

   // GCValues_t valEntry1973;
   // valEntry1973.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   // gClient->GetColorByName("#000000",valEntry1973.fForeground);
   // gClient->GetColorByName("#e8e8e8",valEntry1973.fBackground);
   // valEntry1973.fFillStyle = kFillSolid;
   // valEntry1973.fFont = ufont->GetFontHandle();
   // valEntry1973.fGraphicsExposures = kFALSE;
   // uGC = gClient->GetGC(&valEntry1973, kTRUE);

   // TGTextEntry *fTextEntry1973 = new TGTextEntry(fCentralFrame, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   // fTextEntry1973->SetMaxLength(4096);
   // fTextEntry1973->SetAlignment(kTextLeft);
   // fTextEntry1973->SetText("fTextEntry1973");
   // fTextEntry1973->Resize(200,fTextEntry1973->GetDefaultHeight());
   // fCentralFrame->AddFrame(fTextEntry1973, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   // fTextEntry1973->MoveResize(24,32,200,22);

   // ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

   // // graphics context changes
   // GCValues_t valEntry1980;
   // valEntry1980.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   // gClient->GetColorByName("#000000",valEntry1980.fForeground);
   // gClient->GetColorByName("#e8e8e8",valEntry1980.fBackground);
   // valEntry1980.fFillStyle = kFillSolid;
   // valEntry1980.fFont = ufont->GetFontHandle();
   // valEntry1980.fGraphicsExposures = kFALSE;
   // uGC = gClient->GetGC(&valEntry1980, kTRUE);
   // TGTextEntry *fTextEntry1980 = new TGTextEntry(fCentralFrame, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   // fTextEntry1980->SetMaxLength(4096);
   // fTextEntry1980->SetAlignment(kTextLeft);
   // fTextEntry1980->SetText("fTextEntry1980");
   // fTextEntry1980->Resize(200,fTextEntry1980->GetDefaultHeight());
   // fCentralFrame->AddFrame(fTextEntry1980, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   // fTextEntry1980->MoveResize(24,88,200,22);

   // ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

   // // graphics context changes
   // GCValues_t valEntry1987;
   // valEntry1987.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   // gClient->GetColorByName("#000000",valEntry1987.fForeground);
   // gClient->GetColorByName("#e8e8e8",valEntry1987.fBackground);
   // valEntry1987.fFillStyle = kFillSolid;
   // valEntry1987.fFont = ufont->GetFontHandle();
   // valEntry1987.fGraphicsExposures = kFALSE;
   // uGC = gClient->GetGC(&valEntry1987, kTRUE);
   // TGTextEntry *fTextEntry1987 = new TGTextEntry(fCentralFrame, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   // fTextEntry1987->SetMaxLength(4096);
   // fTextEntry1987->SetAlignment(kTextLeft);
   // fTextEntry1987->SetText("fTextEntry1987");
   // fTextEntry1987->Resize(208,fTextEntry1987->GetDefaultHeight());
   // fCentralFrame->AddFrame(fTextEntry1987, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   // fTextEntry1987->MoveResize(24,152,208,22);

   // ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

   // // graphics context changes
   // GCValues_t valEntry1994;
   // valEntry1994.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   // gClient->GetColorByName("#000000",valEntry1994.fForeground);
   // gClient->GetColorByName("#e8e8e8",valEntry1994.fBackground);
   // valEntry1994.fFillStyle = kFillSolid;
   // valEntry1994.fFont = ufont->GetFontHandle();
   // valEntry1994.fGraphicsExposures = kFALSE;
   // uGC = gClient->GetGC(&valEntry1994, kTRUE);
   // TGTextEntry *fTextEntry1994 = new TGTextEntry(fCentralFrame, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   // fTextEntry1994->SetMaxLength(4096);
   // fTextEntry1994->SetAlignment(kTextLeft);
   // fTextEntry1994->SetText("fTextEntry1994");
   // fTextEntry1994->Resize(208,fTextEntry1994->GetDefaultHeight());
   // fCentralFrame->AddFrame(fTextEntry1994, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   // fTextEntry1994->MoveResize(24,200,208,22);

   // ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

   // // graphics context changes
   // GCValues_t valEntry2001;
   // valEntry2001.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   // gClient->GetColorByName("#000000",valEntry2001.fForeground);
   // gClient->GetColorByName("#e8e8e8",valEntry2001.fBackground);
   // valEntry2001.fFillStyle = kFillSolid;
   // valEntry2001.fFont = ufont->GetFontHandle();
   // valEntry2001.fGraphicsExposures = kFALSE;
   // uGC = gClient->GetGC(&valEntry2001, kTRUE);
   // TGTextEntry *fTextEntry2001 = new TGTextEntry(fCentralFrame, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   // fTextEntry2001->SetMaxLength(4096);
   // fTextEntry2001->SetAlignment(kTextLeft);
   // fTextEntry2001->SetText("fTextEntry2001");
   // fTextEntry2001->Resize(192,fTextEntry2001->GetDefaultHeight());
   // fCentralFrame->AddFrame(fTextEntry2001, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   // fTextEntry2001->MoveResize(32,254,192,22);

   // ufont = gClient->GetFont("-*-helvetica-medium-r-*-*-12-*-*-*-*-*-iso8859-1");

   // // graphics context changes
   // GCValues_t valEntry2020;
   // valEntry2020.fMask = kGCForeground | kGCBackground | kGCFillStyle | kGCFont | kGCGraphicsExposures;
   // gClient->GetColorByName("#000000",valEntry2020.fForeground);
   // gClient->GetColorByName("#e8e8e8",valEntry2020.fBackground);
   // valEntry2020.fFillStyle = kFillSolid;
   // valEntry2020.fFont = ufont->GetFontHandle();
   // valEntry2020.fGraphicsExposures = kFALSE;
   // uGC = gClient->GetGC(&valEntry2020, kTRUE);
   // TGTextEntry *fTextEntry2020 = new TGTextEntry(fCentralFrame, new TGTextBuffer(14),-1,uGC->GetGC(),ufont->GetFontStruct(),kSunkenFrame | kOwnBackground);
   // fTextEntry2020->SetMaxLength(4096);
   // fTextEntry2020->SetAlignment(kTextLeft);
   // fTextEntry2020->SetText("fTextEntry2020");
   // fTextEntry2020->Resize(192,fTextEntry2020->GetDefaultHeight());
   // fCentralFrame->AddFrame(fTextEntry2020, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   // fTextEntry2020->MoveResize(32,296,192,22);

   // fCentralFrame->SetLayoutManager(new TGVerticalLayout(fCentralFrame));
   // fCentralFrame->Resize(250,360);
   // fMainFrame->AddFrame(fCentralFrame, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   // fCentralFrame->MoveResize(600,20,250,360);

//-----------------------------------------------------------------------------
// "fButtons" group frame
//-----------------------------------------------------------------------------
   TGGroupFrame *fButtons = new TGGroupFrame(fMainFrame,"Commands");
   fButtons->SetLayoutBroken(kTRUE);

   TGTextButton *fTextButton = new TGTextButton(fButtons,"gen_fcl",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->Resize(208,24);
   fTextButton->MoveResize(24,32,208,24);
   fButtons->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TJobSub", this, "gen_fcl()");

   fTextButton = new TGTextButton(fButtons,"submit_grid_job",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->Resize(200,24);
   fTextButton->MoveResize(24,72,200,24);
   fButtons->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TJobSub", this, "submit_grid_job()");

   TGTextButton *fTextButton2072 = new TGTextButton(fButtons,"move_dset_to_dcache",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton2072->SetTextJustify(36);
   fTextButton2072->SetMargins(0,0,0,0);
   fTextButton2072->SetWrapLength(-1);
   fTextButton2072->Resize(200,24);
   fButtons->AddFrame(fTextButton2072, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton2072->MoveResize(24,112,200,24);

   TGTextButton *fTextButton2079 = new TGTextButton(fButtons,"check_grid_output",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton2079->SetTextJustify(36);
   fTextButton2079->SetMargins(0,0,0,0);
   fTextButton2079->SetWrapLength(-1);
   fTextButton2079->Resize(216,24);
   fButtons->AddFrame(fTextButton2079, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton2079->MoveResize(16,152,216,24);
   fTextButton2079->Connect("Pressed()", "TJobSub", this, "CheckGridOutput()");

   TGTextButton *fTextButton2086 = new TGTextButton(fButtons,"move_stage_output",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton2086->SetTextJustify(36);
   fTextButton2086->SetMargins(0,0,0,0);
   fTextButton2086->SetWrapLength(-1);
   fTextButton2086->Resize(208,24);
   fButtons->AddFrame(fTextButton2086, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton2086->MoveResize(16,192,208,24);
   fTextButton2086->Connect("Pressed()", "TJobSub", this, "move_stage_output()");
   
   fTextButton = new TGTextButton(fButtons,"copy_log_files",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->Resize(208,24);
   fTextButton->MoveResize(16,240,208,24);
   fButtons->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));

   fTextButton = new TGTextButton(fButtons,"list_pnfs_files",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->Resize(208,24);
   fTextButton->MoveResize(16,280,208,24);
   fButtons->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->Connect("Pressed()", "TJobSub", this, "list_pnfs_files()");

   fTextButton = new TGTextButton(fButtons,"jobsub_q",-1,TGTextButton::GetDefaultGC()(),TGTextButton::GetDefaultFontStruct(),kRaisedFrame);
   fTextButton->SetTextJustify(36);
   fTextButton->SetMargins(0,0,0,0);
   fTextButton->SetWrapLength(-1);
   fTextButton->Resize(216,24);
   fButtons->AddFrame(fTextButton, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fTextButton->MoveResize(16,312,216,24);
   fTextButton->Connect("Pressed()", "TJobSub", this, "jobsub_q()");

   fButtons->SetLayoutManager(new TGVerticalLayout(fButtons));
   fButtons->Resize(250,360);
   fMainFrame->AddFrame(fButtons, new TGLayoutHints(kLHintsLeft | kLHintsTop,2,2,2,2));
   fButtons->MoveResize(320,20,250,360);

   fMainFrame->SetMWMHints(kMWMDecorAll,
                        kMWMFuncAll,
                        kMWMInputModeless);
   fMainFrame->MapSubwindows();

   fMainFrame->Resize(fMainFrame->GetDefaultSize());
   fMainFrame->MapWindow();
   fMainFrame->Resize(939,446);
}  


//-----------------------------------------------------------------------------
void Grid_002() {
  TJobSub* x = new TJobSub(gClient->GetRoot(),150,300);
}

