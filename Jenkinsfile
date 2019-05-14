#!/usr/bin/env groovy

@Library('kanolib')
import build_deb_pkg

stage ('Build') {
    autobuild_repo_pkg 'mercury'
}

stage ('Test') {
    def test_repos = [
        "mercury"
        ]

    make_test(test_repos, "make test") {
    }
}
