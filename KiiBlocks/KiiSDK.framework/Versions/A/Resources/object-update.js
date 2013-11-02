function updateObject(params, context, done){
    Kii.initializeWithSite(context.headers["X-Kii-AppID"], context.headers["X-Kii-AppKey"], "https://dev-jp.internal.kii.com/api");
    var uri = params["uri"];
    var score = params["score"];
    var object = KiiObject.objectWithURI(uri);
    object.set("score", score);
    object.saveAllFields({
      success: function(theObject) {
        done(theObject);
      },
      failure: function(theObject, errorString) {
        done(errorString);
      }
    });
}
