/* jshint browser: true */
/* jshint unused: false */
/* global window, Backbone, arangoHelper, frontendConfig, $ */
(function () {
  'use strict';
  window.QueryManagementSlow = Backbone.Collection.extend({
    model: window.queryManagementModel,

    url: function () {
      var url = arangoHelper.databaseUrl('/_api/query/slow');
      return url;
    },

    deleteSlowQueryHistory: function (callback) {
      var url = arangoHelper.databaseUrl('/_api/query/slow');

      $.ajax({
        url: url,
        type: 'DELETE',
        success: function (result) {
          callback();
        }
      });
    }

  });
}());
