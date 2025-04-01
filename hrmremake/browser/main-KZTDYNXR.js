import{a as K,b as Q}from"./chunk-ZDCJB6ZG.js";import{Fa as s,Ga as h,ba as Y,c as B,d as L,e as z,ea as Z,g as U,h as G,i as V,k as $,l as m,m as J,n as W,o as X}from"./chunk-FVZY75PA.js";import{Ab as f,Bb as g,Cb as j,G as A,Ia as P,Vb as y,W as R,Ya as T,_ as F,_a as E,aa as d,ab as I,bc as v,cb as x,cc as _,eb as N,f as w,fa as p,fb as O,ga as c,la as u,oa as M,r as b,rb as D,yc as H}from"./chunk-7U7RWSPH.js";var ce=()=>["/home-page"],q=(()=>{class r{static{this.\u0275fac=function(o){return new(o||r)}}static{this.\u0275cmp=u({type:r,selectors:[["app-page-not-found"]],standalone:!0,features:[v],decls:8,vars:2,consts:[[1,"container"],[1,"head"],[1,"body"],["type","button","mat-button","",3,"routerLink"]],template:function(o,n){o&1&&(f(0,"main")(1,"div",0)(2,"h1",1),y(3," Oops! "),g(),f(4,"p",2),y(5," 404 - PAGE NOT FOUND "),g(),f(6,"button",3),y(7," GO TO HOMEPAGE "),g()()()),o&2&&(T(6),D("routerLink",_(1,ce)))},dependencies:[Z,Y,X,J],styles:["main[_ngcontent-%COMP%]{width:100%;height:100%;overflow:hidden}.container[_ngcontent-%COMP%]{width:max-content;height:auto;margin:12.5% auto;text-align:center}.head[_ngcontent-%COMP%]{font-size:128px;line-height:1.2;background:radial-gradient(circle,#3f5efb,#fc466b);background-clip:text;-webkit-background-clip:text;-webkit-text-fill-color:transparent;display:inline-block}.body[_ngcontent-%COMP%]{font-size:20px;font-weight:700}"]})}}return r})();var ee=(()=>{class r{constructor(e,o,n){this.accountServ=e,this.router=o,this.notifiServ=n}canActivate(){return w(this,null,function*(){return(yield this.accountServ.loadAuthStatus())?!0:(this.notifiServ.openSnackbar("Permission denied"),this.router.navigate([""]),!1)})}static{this.\u0275fac=function(o){return new(o||r)(p(h),p(m),p(s))}}static{this.\u0275prov=d({token:r,factory:r.\u0275fac,providedIn:"root"})}}return r})();var te=[{path:"",pathMatch:"full",redirectTo:"login"},{path:"login",pathMatch:"full",title:"Login",loadComponent:()=>import("./chunk-WJFWH4Z3.js").then(r=>r.LoginComponent)},{path:"reset",title:"Reset Password",loadComponent:()=>import("./chunk-VHSROJGJ.js").then(r=>r.ForgotPasswordComponent)},{path:"home-page",title:"Home",canActivate:[ee],loadChildren:()=>import("./chunk-53QQZZVP.js").then(r=>r.HOMEPAGE_ROUTES)},{path:"**",title:"404 - Not Found",component:q}];var de="@",pe=(()=>{class r{constructor(e,o,n,i,a){this.doc=e,this.delegate=o,this.zone=n,this.animationType=i,this.moduleImpl=a,this._rendererFactoryPromise=null,this.scheduler=c(I,{optional:!0})}ngOnDestroy(){this._engine?.flush()}loadImpl(){return(this.moduleImpl??import("./chunk-XOUNLGY4.js")).catch(o=>{throw new F(5300,!1)}).then(({\u0275createEngine:o,\u0275AnimationRendererFactory:n})=>{this._engine=o(this.animationType,this.doc,this.scheduler);let i=new n(this.delegate,this._engine,this.zone);return this.delegate=i,i})}createRenderer(e,o){let n=this.delegate.createRenderer(e,o);if(n.\u0275type===0)return n;typeof n.throwOnSyntheticProps=="boolean"&&(n.throwOnSyntheticProps=!1);let i=new S(n);return o?.data?.animation&&!this._rendererFactoryPromise&&(this._rendererFactoryPromise=this.loadImpl()),this._rendererFactoryPromise?.then(a=>{let l=a.createRenderer(e,o);i.use(l)}).catch(a=>{i.use(n)}),i}begin(){this.delegate.begin?.()}end(){this.delegate.end?.()}whenRenderingDone(){return this.delegate.whenRenderingDone?.()??Promise.resolve()}static{this.\u0275fac=function(o){E()}}static{this.\u0275prov=d({token:r,factory:r.\u0275fac})}}return r})(),S=class{constructor(t){this.delegate=t,this.replay=[],this.\u0275type=1}use(t){if(this.delegate=t,this.replay!==null){for(let e of this.replay)e(t);this.replay=null}}get data(){return this.delegate.data}destroy(){this.replay=null,this.delegate.destroy()}createElement(t,e){return this.delegate.createElement(t,e)}createComment(t){return this.delegate.createComment(t)}createText(t){return this.delegate.createText(t)}get destroyNode(){return this.delegate.destroyNode}appendChild(t,e){this.delegate.appendChild(t,e)}insertBefore(t,e,o,n){this.delegate.insertBefore(t,e,o,n)}removeChild(t,e,o){this.delegate.removeChild(t,e,o)}selectRootElement(t,e){return this.delegate.selectRootElement(t,e)}parentNode(t){return this.delegate.parentNode(t)}nextSibling(t){return this.delegate.nextSibling(t)}setAttribute(t,e,o,n){this.delegate.setAttribute(t,e,o,n)}removeAttribute(t,e,o){this.delegate.removeAttribute(t,e,o)}addClass(t,e){this.delegate.addClass(t,e)}removeClass(t,e){this.delegate.removeClass(t,e)}setStyle(t,e,o,n){this.delegate.setStyle(t,e,o,n)}removeStyle(t,e,o){this.delegate.removeStyle(t,e,o)}setProperty(t,e,o){this.shouldReplay(e)&&this.replay.push(n=>n.setProperty(t,e,o)),this.delegate.setProperty(t,e,o)}setValue(t,e){this.delegate.setValue(t,e)}listen(t,e,o){return this.shouldReplay(e)&&this.replay.push(n=>n.listen(t,e,o)),this.delegate.listen(t,e,o)}shouldReplay(t){return this.replay!==null&&t.startsWith(de)}};function oe(r="animations"){return N("NgAsyncAnimations"),M([{provide:x,useFactory:(t,e,o)=>new pe(t,e,o,r),deps:[H,U,O]},{provide:P,useValue:r==="noop"?"NoopAnimations":"BrowserAnimations"}])}var re=(()=>{class r{constructor(e){this.notifiServ=e}handleError(e,o,n){if(n.status!=500)if(console.log(n.message),n.error instanceof Blob){let i=new FileReader;i.onloadend=()=>{let a=i.result,l=JSON.parse(a);this.notifiServ.openSnackbar("Encountered a problem with file reader.")},i.readAsText(n.error)}else this.notifiServ.openSnackbar(n.error.Message);else e.url.includes("LogoutAccount")||this.notifiServ.openSnackbar("Encountered a problem, please try again");return o(e)}static{this.\u0275fac=function(o){return new(o||r)(p(s))}}static{this.\u0275prov=d({token:r,factory:r.\u0275fac,providedIn:"root"})}}return r})();var ne=(r,t)=>{let e=c(s),o=c(m),n=c(h),i=c(re),a=n.tokens().token,l=r.clone({setHeaders:a?{Authorization:`Bearer ${a}`}:{}});return t(l).pipe(A(C=>C.status===401?me(r,t,n,e,o):b(()=>i.handleError(r,t,C))))};function me(r,t,e,o,n){let i={Token:e.tokens().token,RefreshToken:e.tokens().refreshToken};return e.refreshToken(i).pipe(R(a=>(e.storeNewTokens(a.TokenData),e.tokens.update(l=>l={token:a.TokenData.Token,refreshToken:a.TokenData.RefreshToken}),r=r.clone({setHeaders:{Authorization:`Bearer ${a.TokenData.Token}`}}),t(r))),A(a=>b(()=>{e.logout(),o.openSnackbar("Token has expired. Please login again."),n.navigateByUrl("")})))}var ie={providers:[W(te),V(),oe(),B(z(),L([ne])),m,K,Q,s,h]};var ae=(()=>{class r{constructor(){this.title="HRMRemake"}static{this.\u0275fac=function(o){return new(o||r)}}static{this.\u0275cmp=u({type:r,selectors:[["app-root"]],standalone:!0,features:[v],decls:1,vars:0,template:function(o,n){o&1&&j(0,"router-outlet")},dependencies:[$]})}}return r})();G(ae,ie).catch(r=>console.error(r));
