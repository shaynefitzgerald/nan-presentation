import { expect } from 'chai';

let addon;

describe('Slicker Algorithm', () => {
  beforeEach(() => {
    addon = require('native/slicker-compute');
  });
  describe('When module is initialized', () =>{
    it('should return an object "computeSlickerArea" defined as a function', () => {
      expect(addon.computeSlickerArea).to.not.be.undefined;
      expect(typeof addon.computeSlickerArea).to.equal('function');
    });
  });
  describe('computeSlickerArea', () => {
    describe('When invoked with args (<0,0>, <1,0>, <0,1>)', () => {
      it('should return 0.5', () => {
        const area = addon.computeSlickerArea([0,0,1,0,0,1]);
        expect(area).to.equal(0.5);
      });
    })
    describe('When invoked with incorrect length arguments', () => {
      it('should throw "RangeError: Argument length must be even"', () => {
        const invalid = addon.computeSlickerArea.bind(addon, [0,0,1,0,0]);
        expect(invalid).to.throw(RangeError);
      });
    });
    describe('When invoked with an argument other than an array', () => {
      it('should throw TypeError with message "Argument must be an array"', () => {
        const invalid = addon.computeSlickerArea.bind(addon, -1);
        expect(invalid).to.throw(TypeError);
      });
    });
  })
});