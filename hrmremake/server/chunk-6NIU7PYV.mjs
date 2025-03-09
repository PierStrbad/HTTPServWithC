import './polyfills.server.mjs';
import{c as J}from"./chunk-P34BYG2J.mjs";import{a as q,b as ee}from"./chunk-FWMTLZ73.mjs";import{O as K,R as Q,qa as s,ra as h}from"./chunk-42VY2SIW.mjs";import{d as L,e as z,f as U,k as G,l as V,n as $,p as W,r as m,s as X,t as Y,u as Z}from"./chunk-LH2VRXI6.mjs";import{$ as d,A,Bc as B,Ca as P,Q as R,Rb as y,U as F,Ua as T,W as p,Wa as x,Ya as E,Zb as v,_a as I,_b as _,aa as l,ab as N,bb as O,fa as u,ia as M,l as b,nb as D,wb as f,xb as g,xc as H,yb as j}from"./chunk-DQBLOAAZ.mjs";import{h as w}from"./chunk-VVCT4QZE.mjs";var te=(()=>{class r{constructor(){this.title="HRMRemake"}static{this.\u0275fac=function(o){return new(o||r)}}static{this.\u0275cmp=u({type:r,selectors:[["app-root"]],standalone:!0,features:[v],decls:1,vars:0,template:function(o,n){o&1&&j(0,"router-outlet")},dependencies:[W]})}}return r})();var de=()=>["/home-page"],oe=(()=>{class r{static{this.\u0275fac=function(o){return new(o||r)}}static{this.\u0275cmp=u({type:r,selectors:[["app-page-not-found"]],standalone:!0,features:[v],decls:8,vars:2,consts:[[1,"container"],[1,"head"],[1,"body"],["type","button","mat-button","",3,"routerLink"]],template:function(o,n){o&1&&(f(0,"main")(1,"div",0)(2,"h1",1),y(3," Oops! "),g(),f(4,"p",2),y(5," 404 - PAGE NOT FOUND "),g(),f(6,"button",3),y(7," GO TO HOMEPAGE "),g()()()),o&2&&(T(6),D("routerLink",_(1,de)))},dependencies:[Q,K,Z,X],styles:["main[_ngcontent-%COMP%]{width:100%;height:100%;overflow:hidden}.container[_ngcontent-%COMP%]{width:max-content;height:auto;margin:12.5% auto;text-align:center}.head[_ngcontent-%COMP%]{font-size:128px;line-height:1.2;background:radial-gradient(circle,#3f5efb,#fc466b);background-clip:text;-webkit-background-clip:text;-webkit-text-fill-color:transparent;display:inline-block}.body[_ngcontent-%COMP%]{font-size:20px;font-weight:700}"]})}}return r})();var re=(()=>{class r{constructor(e,o,n){this.accountServ=e,this.router=o,this.notifiServ=n}canActivate(){return w(this,null,function*(){return(yield this.accountServ.loadAuthStatus())?!0:(this.notifiServ.openSnackbar("Permission denied"),this.router.navigate([""]),!1)})}static{this.\u0275fac=function(o){return new(o||r)(d(h),d(m),d(s))}}static{this.\u0275prov=p({token:r,factory:r.\u0275fac,providedIn:"root"})}}return r})();var ne=[{path:"",pathMatch:"full",redirectTo:"login"},{path:"login",pathMatch:"full",title:"Login",loadComponent:()=>import("./chunk-LZ3IK4GJ.mjs").then(r=>r.LoginComponent)},{path:"reset",title:"Reset Password",loadComponent:()=>import("./chunk-IANAHSKP.mjs").then(r=>r.ForgotPasswordComponent)},{path:"home-page",title:"Home",canActivate:[re],loadChildren:()=>import("./chunk-MPMPN7BV.mjs").then(r=>r.HOMEPAGE_ROUTES)},{path:"**",title:"404 - Not Found",component:oe}];var he="@",ue=(()=>{class r{constructor(e,o,n,i,a){this.doc=e,this.delegate=o,this.zone=n,this.animationType=i,this.moduleImpl=a,this._rendererFactoryPromise=null,this.scheduler=l(E,{optional:!0})}ngOnDestroy(){this._engine?.flush()}loadImpl(){return(this.moduleImpl??import("./chunk-JSF6GJ24.mjs")).catch(o=>{throw new F(5300,!1)}).then(({\u0275createEngine:o,\u0275AnimationRendererFactory:n})=>{this._engine=o(this.animationType,this.doc,this.scheduler);let i=new n(this.delegate,this._engine,this.zone);return this.delegate=i,i})}createRenderer(e,o){let n=this.delegate.createRenderer(e,o);if(n.\u0275type===0)return n;typeof n.throwOnSyntheticProps=="boolean"&&(n.throwOnSyntheticProps=!1);let i=new S(n);return o?.data?.animation&&!this._rendererFactoryPromise&&(this._rendererFactoryPromise=this.loadImpl()),this._rendererFactoryPromise?.then(a=>{let c=a.createRenderer(e,o);i.use(c)}).catch(a=>{i.use(n)}),i}begin(){this.delegate.begin?.()}end(){this.delegate.end?.()}whenRenderingDone(){return this.delegate.whenRenderingDone?.()??Promise.resolve()}static{this.\u0275fac=function(o){x()}}static{this.\u0275prov=p({token:r,factory:r.\u0275fac})}}return r})(),S=class{constructor(t){this.delegate=t,this.replay=[],this.\u0275type=1}use(t){if(this.delegate=t,this.replay!==null){for(let e of this.replay)e(t);this.replay=null}}get data(){return this.delegate.data}destroy(){this.replay=null,this.delegate.destroy()}createElement(t,e){return this.delegate.createElement(t,e)}createComment(t){return this.delegate.createComment(t)}createText(t){return this.delegate.createText(t)}get destroyNode(){return this.delegate.destroyNode}appendChild(t,e){this.delegate.appendChild(t,e)}insertBefore(t,e,o,n){this.delegate.insertBefore(t,e,o,n)}removeChild(t,e,o){this.delegate.removeChild(t,e,o)}selectRootElement(t,e){return this.delegate.selectRootElement(t,e)}parentNode(t){return this.delegate.parentNode(t)}nextSibling(t){return this.delegate.nextSibling(t)}setAttribute(t,e,o,n){this.delegate.setAttribute(t,e,o,n)}removeAttribute(t,e,o){this.delegate.removeAttribute(t,e,o)}addClass(t,e){this.delegate.addClass(t,e)}removeClass(t,e){this.delegate.removeClass(t,e)}setStyle(t,e,o,n){this.delegate.setStyle(t,e,o,n)}removeStyle(t,e,o){this.delegate.removeStyle(t,e,o)}setProperty(t,e,o){this.shouldReplay(e)&&this.replay.push(n=>n.setProperty(t,e,o)),this.delegate.setProperty(t,e,o)}setValue(t,e){this.delegate.setValue(t,e)}listen(t,e,o){return this.shouldReplay(e)&&this.replay.push(n=>n.listen(t,e,o)),this.delegate.listen(t,e,o)}shouldReplay(t){return this.replay!==null&&t.startsWith(he)}};function ie(r="animations"){return N("NgAsyncAnimations"),M([{provide:I,useFactory:(t,e,o)=>new ue(t,e,o,r),deps:[B,G,O]},{provide:P,useValue:r==="noop"?"NoopAnimations":"BrowserAnimations"}])}var ae=(()=>{class r{constructor(e){this.notifiServ=e}handleError(e,o,n){if(n.status!=500)if(console.log(n.message),n.error instanceof Blob){let i=new FileReader;i.onloadend=()=>{let a=i.result,c=JSON.parse(a);this.notifiServ.openSnackbar(c.Message)},i.readAsText(n.error)}else this.notifiServ.openSnackbar(n.error.Message);else e.url.includes("LogoutAccount")||this.notifiServ.openSnackbar("Encountered a problem, please try again");return o(e)}static{this.\u0275fac=function(o){return new(o||r)(d(s))}}static{this.\u0275prov=p({token:r,factory:r.\u0275fac,providedIn:"root"})}}return r})();var se=(r,t)=>{let e=l(s),o=l(m),n=l(h),i=l(ae),a=n.tokens().token,c=r.clone({setHeaders:a?{Authorization:`Bearer ${a}`}:{}});return t(c).pipe(A(C=>C.status===401?fe(r,t,n,e,o):b(()=>i.handleError(r,t,C))))};function fe(r,t,e,o,n){let i={Token:e.tokens().token,RefreshToken:e.tokens().refreshToken};return e.refreshToken(i).pipe(R(a=>(e.storeNewTokens(a.TokenData),e.tokens.update(c=>c={token:a.TokenData.Token,refreshToken:a.TokenData.RefreshToken}),r=r.clone({setHeaders:{Authorization:`Bearer ${a.TokenData.Token}`}}),t(r))),A(a=>b(()=>{e.logout(),o.openSnackbar("Token has expired. Please login again."),n.navigateByUrl("")})))}var ce={providers:[Y(ne),$(),ie(),L(U(),z([se])),m,q,ee,s,h]};var ge={providers:[J()]},le=H(ce,ge);var ye=()=>V(te,le),st=ye;export{st as a};
