#!/usr/bin/env groovy

@Library('kanolib')
import build_deb_pkg

stage ('Test') {
    def test_repos = [
    ]

    make_test(test_repos) {
		sh "conan remote add dev-server http://dev.kano.me:9300"

		sh "make build-release"
		sh "make build-debug"
    }
}

stage ('Build') {
    autobuild_repo_pkg 'mercury'
}
